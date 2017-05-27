#include "window.h"

void window_draw_callback(PtkWindow *window, PtkCanvas *canvas, int width, int heigh) {
  ptk_set_canvas(canvas);
  ptk_set_draw_color(64, 64, 64, 1);
  ptk_draw_rectangle(0, 0, width, heigh);

  ptk_set_draw_color(255, 255, 255, 1);
  ptk_draw_text("hello", 5);
}

void mouse_press_callback(PtkWindow *window, PtkMouseType button, unsigned int time, int x, int y) {
  PtkMenu *popmenu;

  switch (button) {
    case PTK_MOUSE_UNKNOWN:
      break;
    case PTK_MOUSE_LEFT:
      break;
    case PTK_MOUSE_RIGHT:
      popmenu = phi_popmenu_new();
      ptk_menu_popup(window, popmenu, time, x, y);
      break;
  }
}

void mouse_release_callback(PtkWindow *window, PtkMouseType button, unsigned int time, int x, int y) {
}

void keyboard_input_callback(PtkWindow *window, const char *text) {

}

PhiWindow *phi_window_new(char *path, PlatformParam param) {
  PhiWindow *window = (PhiWindow *) malloc(sizeof(PhiWindow));
  PhiMenuBar *menu_bar = phi_menu_bar_new();
  PtkWindow *ptk_widget = ptk_window_new(WIDTH, HEIGHT,
                                        menu_bar->ptk_widget, param);

  window->ptk_widget = ptk_widget;
  window->menu_bar = menu_bar;
  window->view_list = NULL;
  window->next = NULL;

  ptk_window_set_title(ptk_widget, TITLE);
  ptk_window_set_window_draw_callback(ptk_widget, &window_draw_callback);
  ptk_window_set_mouse_press_callback(ptk_widget, &mouse_press_callback);
  ptk_window_set_mouse_release_callback(ptk_widget, &mouse_release_callback);
  ptk_window_set_keyboard_input_callback(ptk_widget, &keyboard_input_callback);

  return window;
}

void phi_window_destroy(PhiWindow *window) {
  PhiView *view;
  // Destroy all views in this window
  while (window->view_list != NULL) {
    view = window->view_list;
    window->view_list = view->next;
    phi_view_destroy(view);
  }
}
