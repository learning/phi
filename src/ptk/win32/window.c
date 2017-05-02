#include <stdio.h>
#include "../window.h"
#include "../pevent.h"

/* Manage window instances */
typedef struct _window_node {
  PtkWindow window;
  void (*drawing)(PtkCanvas *, int, int);
  void (*press)(PtkWindow, PtkButtonType, unsigned int, int, int);
  void (*release)(PtkWindow, PtkButtonType, unsigned int, int, int);
  struct _window_node *next;
} _WindowNode;

_WindowNode *_window_list = NULL;

void _addWindow(PtkWindow window) {
  if (_window_list == NULL) {
    // List is empty
    _window_list = (_WindowNode *) malloc(sizeof(_WindowNode));
    _window_list->window = window;
    _window_list->press = NULL;
    _window_list->release = NULL;
    _window_list->drawing = NULL;
    _window_list->next = NULL;
  } else {
    // List is not empty, get the first node
    _WindowNode *node = _window_list;
    // Get the last node
    while (node->next != NULL) {
      node = node->next;
    }
    node->next = (_WindowNode *) malloc(sizeof(_WindowNode));
    node->next->window = window;
    node->next->press = NULL;
    node->next->release = NULL;
    node->next->drawing = NULL;
    node->next->next = NULL;
  }
}

void _removeWindow(HWND hWnd) {
  if (_window_list != NULL) {
    _WindowNode *node = _window_list;
    _WindowNode *next = NULL;

    if (node->window.instance == hWnd) {
      // The only window node
      free(node);
      _window_list = NULL;
    } else {
      while (node->next != NULL) {
        next = node->next;

        // Check the next
        if (next->window.instance == hWnd) {
          node->next = next->next;
          free(next);
          next = NULL;
          break;
        } else {
          node = next;
        }
      }
    }

  }
}

_WindowNode *_getWindow(HWND hWnd) {
  if (_window_list != NULL) {
    // List is not empty, get the first node
    _WindowNode *node = _window_list;

    while (1) {
      if (node->window.instance == hWnd) {
        return node;
      }
      if (node->next != NULL) {
        node = node->next;
      } else {
        return NULL;
      }
    }

  }
  return NULL;
}



VOID _window_CloseCallback() {
  PtkEvent evt = { "window_close" };
  ptk_dispatch(PTK_WINDOW_CLOSE, evt);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  HDC          hdc;
  PAINTSTRUCT  ps;

  _WindowNode  *node = _getWindow(hWnd);
  RECT         rect;

  switch(message) {
    case WM_PAINT:
      if (node != NULL) {
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);
        node->drawing(hdc, rect.right - rect.left, rect.bottom - rect.top);
        EndPaint(hWnd, &ps);
      }
      return 0;
    case WM_LBUTTONDOWN:
      if (node != NULL) node->press(node->window, PTK_BUTTON_LEFT, 0, LOWORD(lParam), HIWORD(lParam));
      return 0;
    case WM_MBUTTONDOWN:
      if (node != NULL) node->press(node->window, PTK_BUTTON_MIDDLE, 0, LOWORD(lParam), HIWORD(lParam));
      return 0;
    case WM_RBUTTONDOWN:
      if (node != NULL) node->press(node->window, PTK_BUTTON_RIGHT, 0, LOWORD(lParam), HIWORD(lParam));
      return 0;
    case WM_LBUTTONUP:
      if (node != NULL) node->release(node->window, PTK_BUTTON_LEFT, 0, LOWORD(lParam), HIWORD(lParam));
      return 0;
    case WM_MBUTTONUP:
      if (node != NULL) node->release(node->window, PTK_BUTTON_MIDDLE, 0, LOWORD(lParam), HIWORD(lParam));
      return 0;
    case WM_RBUTTONUP:
      if (node != NULL) node->release(node->window, PTK_BUTTON_RIGHT, 0, LOWORD(lParam), HIWORD(lParam));
      return 0;
    case WM_DESTROY:
      _removeWindow(hWnd);
      _window_CloseCallback();
      return 0;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

PtkWindow ptk_window_new(int width, int height, PtkMenuBar *menuBar, PlatformParam param) {
  HWND hWnd;
  WNDCLASS wndClass;

  wndClass.style          = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc    = WndProc;
  wndClass.cbClsExtra     = 0;
  wndClass.cbWndExtra     = 0;
  wndClass.hInstance      = param.hInstance;
  wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.lpszMenuName   = NULL;
  wndClass.lpszClassName  = TEXT("GettingStarted");

  RegisterClass(&wndClass);

  RECT rect = RECT();
  rect.top = 0;
  rect.left = 0;
  rect.bottom = height;
  rect.right = width;
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

  hWnd = CreateWindow(
    TEXT("GettingStarted"),   // window class name
    TEXT("Title"),            // window caption
    WS_OVERLAPPEDWINDOW,      // window style
    CW_USEDEFAULT,            // initial x position
    CW_USEDEFAULT,            // initial y position
    rect.right - rect.left,   // initial x size
    rect.bottom - rect.top,   // initial y size
    NULL,                     // parent window handle
    NULL,                     // window menu handle
    param.hInstance,          // program instance handle
    NULL);                    // creation parameters

  if (menuBar != NULL) {
    SetMenu(hWnd, menuBar);
  }

  ShowWindow(hWnd, param.iCmdShow);
  UpdateWindow(hWnd);

  PtkWindow window = { hWnd };
  _addWindow(window);

  return window;
}

void ptk_window_set_title(PtkWindow window, const char title[]) {
  SetWindowText(window.instance, title);
}

void ptk_window_set_drawing_callback(PtkWindow window, void (*fpointer)(PtkCanvas *, int, int)) {
  _WindowNode *node = _getWindow(window.instance);
  if (node != NULL) {
    node->drawing = fpointer;
  }
}

void ptk_window_set_button_press_callback(PtkWindow window, void (*fpointer)(PtkWindow, PtkButtonType, unsigned int, int, int)) {
  _WindowNode *node = _getWindow(window.instance);
  if (node != NULL) {
    node->press = fpointer;
  }
}

void ptk_window_set_button_release_callback(PtkWindow window, void (*fpointer)(PtkWindow, PtkButtonType, unsigned int, int, int)) {
  _WindowNode *node = _getWindow(window.instance);
  if (node != NULL) {
    node->release = fpointer;
  }
}
