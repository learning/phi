#include <stdio.h>
#include "app.h"

int windowCount = 0;

PhiWindow *window_list;
PhiBuffer *buffer_list;
// PtkTextLayout *layout;

void window_close_callback(PtkEvent event) {
  --windowCount;
  if (windowCount <= 0) {
    ptk_main_quit();
  }
}

void phi_init(PlatformParam param) {
  ptk_add_listener(PTK_WINDOW_CLOSE, &window_close_callback);

  window_list = phi_window_new(param);
  buffer_list = phi_buffer_new(0);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  phi_window_add_view(window_list, buffer_list);
  ++windowCount;

  // phi_window_new(param);
  // ++windowCount;
}
