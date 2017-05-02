#ifndef __PHI_VIEW__
#define __PHI_VIEW__

#include "buffer.h"
#include "selection.h"

/*
 * Struct: PhiView
 * ---------------
 *   Represents a view into a text buffer.
 *   Note that multiple views may refer to the same buffer,
 *   but they have their own unique selection and geometry.
 */
typedef struct phi_view_t {
  PhiBuffer *buffer;
  PhiSelection *selection;
  struct phi_view_t *next;
} PhiView;


/*
 * Function: phi_view_new
 * ----------------------
 *   Create a new view for a text buffer
 *
 *   returns: the new view just create
 */
PhiView *phi_view_new(PhiBuffer *buffer);

/*
 * Function: phi_view_destroy
 * --------------------------
 *   Destroy a view
 *
 *   view: which view to be destroy
 */
void phi_view_destroy(PhiView *view);

#endif
