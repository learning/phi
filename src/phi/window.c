#include "window.h"

PhiWindow *phi_window_new(char *path, PlatformParam param) {
  PhiWindow *window = (PhiWindow *) malloc(sizeof(PhiWindow));
  PtkMenuBar *menu_bar = phi_menu_bar_init();
  PtkWindow *ptk_window = ptk_window_new(WIDTH, HEIGHT, menu_bar->ptk_widget, param);

  window->ptk_widget = ptk_widget;
  window->menu_bar = menu_bar;
  window->view_list = NULL;
  window->next = NULL;

  ptk_window_set_title(ptk_widget, TITLE);
  // ptk_window_set_drawing_callback(ptk_window, &window_draw_callback);
  // ptk_window_set_button_press_callback(ptk_window, &button_press_callback);
  // ptk_window_set_button_release_callback(ptk_window, &button_release_callback);
  // ptk_window_set_input_callback(ptk_window, &input_callback);
  return window;
}
