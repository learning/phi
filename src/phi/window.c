#include "window.h"

void input_callback(PtkWindow *window, const char *str) {
  // phi_buffer_insert(pb, pb->length, str);
  // ptk_redraw(window, 0, 0, 400, 400);
}

void button_press_callback(PtkWindow *window, PtkButtonType button, unsigned int time, int x, int y) {
  PtkMenu *popmenu;

  switch (button) {
    case PTK_BUTTON_UNKNOWN:
      break;
    case PTK_BUTTON_LEFT:
      ptk_move_to(x, y);
      break;
    case PTK_BUTTON_MIDDLE:
      break;
    case PTK_BUTTON_RIGHT:
      popmenu = phi_popmenu_new();
      ptk_menu_popup(window, popmenu, time, x, y);
      break;
  }
}

void button_release_callback(PtkWindow *window, PtkButtonType button, unsigned int time, int x, int y) {
}

void window_draw_callback(PtkWindow *window, PtkCanvas *canvas, int width, int height) {
  printf("window_draw_callback.\n");
  ptk_set_canvas(canvas);

  /* draw tabs */
//  printf("window: %ld.\n", (long) window->canvas);
  // int num_tabs = 0;
  // PhiView *node = window_list->view_list;
  // while (node != NULL) {
  //   ++i;
  //   node = node->next;
  // }
  // printf("total views: %d.\n", i);
  /* draw view */
  ptk_set_draw_color(253, 246, 228, 1);
  ptk_draw_rectangle(0, 0, width, height);
  ptk_set_draw_color(0, 0, 0, 0.5);
  ptk_draw_rectangle(10, 10, width - 20, height - 20);
  // if (layout == NULL) layout = ptk_text_layout_new();
  // ptk_set_draw_color(0, 0, 0, 1);
  // ptk_draw_text(layout, pb->buffer, pb->length);
}

PhiWindow *phi_window_new(PlatformParam param) {
  PhiWindow *window = (PhiWindow *) malloc(sizeof(PhiWindow));
  PtkMenuBar *menuBar = phi_menu_bar_init();
  PtkWindow *ptk_window = ptk_window_new(WIDTH, HEIGHT, menuBar, param);

  window->ptk_window = ptk_window;
  window->view_list = NULL;
  window->next = NULL;

  ptk_window_set_title(ptk_window, TITLE);
  ptk_window_set_drawing_callback(ptk_window, &window_draw_callback);
  ptk_window_set_button_press_callback(ptk_window, &button_press_callback);
  ptk_window_set_button_release_callback(ptk_window, &button_release_callback);
  ptk_window_set_input_callback(ptk_window, &input_callback);
  return window;
}

void phi_window_add_view(PhiWindow *window, PhiBuffer *buffer) {
  if (window->view_list == NULL) {
    window->view_list = phi_view_new(buffer);
  } else {
    PhiView *last = window->view_list;
    while (last->next != NULL) last = last->next;
    last->next = phi_view_new(buffer);
  }
}
