#ifndef __PHI_BACKEND_SELECTION__
#define __PHI_BACKEND_SELECTION__

#include "types.h"
#include "region.h"

typedef struct
{
  phi_region *regions; // Regions' linked list
  phi_region *last_region; // The last region
} phi_selection;

/*
 * Function: phi_selection_new
 * ----------------------
 *   Create a new selection without any regions
 *
 *   returns: phi_selection pointer
 */
phi_selection *phi_selection_new(phi_region *regions);

/*
 * Function: phi_selection_destroy
 * ----------------------
 *   Destroy a selection and free memory
 */
void phi_selection_destroy(phi_selection *selection);

/*
 * Function: phi_selection_clear
 * ----------------------
 *   Clear all regions in the selection
 */
void phi_selection_clear(phi_selection *selection);

/*
 * Function: phi_selection_add
 * ----------------------
 *   Add region(s) to the selection
 */
void phi_selection_add(phi_selection *selection, phi_region *region);

/*
 * Function: phi_selection_remove
 * ----------------------
 *   Remove a region in the selection
 */
void phi_selection_remove(phi_selection *selection, phi_region *region);

/*
 * Function: phi_selection_contains
 * ----------------------
 *   Tell if the selection contains the region
 *
 *   returns: Is the selection contains the region?
 */
bool phi_selection_contains(phi_selection *selection, phi_region *region);

#endif

