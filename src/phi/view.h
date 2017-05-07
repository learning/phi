/*
 * phi/view.h
 *
 * Represent a view of a buffer
 * A view has a buffer, but a buffer can holds many views
 * And a view has a text selection, it's set of multiple regions
 */
#ifndef __PHI_VIEW__
#define __PHI_VIEW__

#include "buffer.h"
#include "region.h"

typedef struct phi_view_t {
  PhiBuffer *buffer; // The phi text buffer for this view
  PhiRegion *selection; // The selection is a region set of this view
  struct phi_view_t *next; // It's a linked list for PhiWindow
} PhiView;

/*
 * Function: phi_view_new
 * ----------------------
 *   Create a phi view
 *
 *   buffer: the phi buffer, required
 */
PhiView *phi_view_new(PhiBuffer *buffer);

/*
 * Function: phi_view_destroy
 * ----------------------
 *   Destroy a phi view
 */
void phi_view_destroy();

#endif
