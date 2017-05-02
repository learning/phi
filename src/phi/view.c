#include "view.h"

PhiView *phi_view_new(PhiBuffer *buffer) {
  PhiView *view = (PhiView *) malloc(sizeof(PhiView));
  PhiSelection *selection = phi_selection_new();
  view->buffer = buffer;
  view->selection = selection;
  view->next = NULL;
  return view;
}

void phi_view_destroy(PhiView *view) {
  phi_selection_destroy(view->selection);
  free(view);
}
