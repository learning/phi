#ifndef __PHI_SELECTION__
#define __PHI_SELECTION__

#include "region.h"

/*
 * Struct: PhiSelection
 * --------------------
 *   Maintains a set of Regions, ensuring that none overlap.
 *   The regions are kept in sorted order.
 */
typedef struct {
  PhiRegion *region_list;
} PhiSelection;

/*
 * Function: phi_selection_new
 * ---------------------------
 *   Create a new selection of a view, and return it.
 *   By initial, it contains one region (0, 0)
 *
 *   returns: the new selection just create
 */
PhiSelection *phi_selection_new();

/*
 * Function: phi_selection_destroy
 * -------------------------------
 *   Destroy a selection
 *
 *   selection: which selection to be destroy
 */
void phi_selection_destroy(PhiSelection *selection);

// PhiRegion *get_last_region();

#endif
