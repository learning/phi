#include "view.h"

PhiView *phi_view_new(PhiBuffer *buffer) {
  PhiView *view = (PhiView *) malloc(sizeof(PhiView));

  view->buffer = buffer;
  view->selection = phi_region_new(0, 0);
  view->next = NULL;

  return view;
}

void phi_view_destroy(PhiView *view) {
  PhiRegion *region;
  // Destroy all regions in this view
  while (view->selection != NULL) {
    region = view->selection;
    view->selection = region->next;
    phi_region_destroy(region);
  }
  // TODO: Remove this view's reference from buffer
  // If this buffer no longer used by any views, then destroy it.
  // Is this buffer has been modified? If yes, ask user wether to save it.
}
