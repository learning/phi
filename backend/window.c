#include "window.h"

uint window_id = 1;

phi_window *phi_window_new() {
  phi_window *window = (phi_window *) malloc(sizeof(phi_window));
  window->id = window_id++;
  window->panes = (phi_pane **) malloc(sizeof(phi_pane *) * MAX_PANES);
  window->layout = SINGLE;
  window->panes[0] = phi_pane_new(NULL);
  window->panes[1] = NULL;
  window->panes[2] = NULL;
  window->panes[3] = NULL;
  return window;
}

void phi_window_destroy(phi_window *window) {
  for (int i = 0; i < MAX_PANES; i++) {
    if (window->panes[i] != NULL) {
      phi_pane_destroy(window->panes[i], NULL);
    }
  }
  free(window->panes);
  free(window);
}

void phi_window_change_layout(phi_window *window, phi_layout layout) {
  uint max_index; // the last pane's index

  window->layout = layout;

  switch (layout) {
    default:
    case SINGLE:
      max_index = 0;
      break;
    case COLUMN_2:
    case ROW_2:
      max_index = 1;
      break;
    case COLUMN_3:
    case ROW_3:
      max_index = 2;
      break;
    case COLUMN_4:
    case GRID_4:
      max_index = 3;
      break;
  }

  for (int i = MAX_PANES - 1; i >= max_index; i--) {
    // pane to destroy
    phi_pane_destroy(window->panes[i], window->panes[max_index]);
  }
}
