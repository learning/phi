#include <stdio.h>
#include "app.h"

int windowCount = 0;

PhiWindow *window_list; // opened windows' list
PhiBuffer *buffer_list; // opened buffers' list

void window_close_callback(PtkEvent event) {
  PtkWindow *ptk_widget = (PtkWindow *) event.target;

  // detect which window has been closed
  PhiWindow *prev = NULL;
  PhiWindow *window = window_list;

  do {
    if (window->ptk_widget == ptk_widget) {
      if (prev == NULL) {
        window_list = window->next;
        printf("window_list = window->next;\n");
      } else {
        prev->next = window->next;
        printf("prev->next = window->next;\n");
      }
      printf("phi_window_destroy(window);\n");
      phi_window_destroy(window);
      --windowCount;
      break;
    } else {
      prev = window;
      printf("prev = window;\n");
    }
  } while ((window = window->next));


  // If all windows are closed, exit;
  if (windowCount <= 0) {
    ptk_main_quit();
  }
}

void phi_load_state(PlatformParam param) {
  // TODO: restore last state
  if (1) {
    // test multiple windows
    PhiWindow *window1 = phi_window_new(NULL, param);
    ++windowCount;
    PhiWindow *window2 = phi_window_new(NULL, param);
    ++windowCount;
    PhiWindow *window3 = phi_window_new(NULL, param);
    ++windowCount;
    window_list = window1;
    window1->next = window2;
    window2->next = window3;
  } else {
    window_list = phi_window_new(NULL, param);
    ++windowCount;
  }
}

void phi_init(PlatformParam param) {
  ptk_add_listener(PTK_WINDOW_CLOSE, &window_close_callback);

  phi_load_state(param);
  // TODO: has arguments, open specified path

}
