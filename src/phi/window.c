#include "window.h"

void window_draw_callback(PtkWindow *window, PtkCanvas *canvas, int width, int heigh) {
  ptk_set_canvas(canvas);
  ptk_set_draw_color(64, 64, 64, 1);
  ptk_draw_rectangle(0, 0, width, heigh);

  ptk_set_draw_color(255, 255, 255, 1);
  ptk_draw_text("hello", 5);
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
  ptk_window_set_drawing_callback(ptk_widget, &window_draw_callback);
  // ptk_window_set_button_press_callback(ptk_window, &button_press_callback);
  // ptk_window_set_button_release_callback(ptk_window, &button_release_callback);
  // ptk_window_set_input_callback(ptk_window, &input_callback);
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
