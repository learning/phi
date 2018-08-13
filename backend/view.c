#include "view.h"

uint view_id = 1;

phi_view *phi_view_new(const char *filename) {
  phi_view *view = (phi_view *) malloc(sizeof(phi_view));
  view->id = view_id++;
  view->file = phi_file_open(filename);
  view->selection = phi_selection_new(NULL);
  view->next = NULL;
  return view;
}

void phi_view_destroy(phi_view *view) {
  phi_selection_destroy(view->selection);
  phi_file_close(view->file);
  free(view);
}
