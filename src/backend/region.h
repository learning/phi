#ifndef __PHI_REGION__
#define __PHI_REGION__

#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

typedef struct _phi_region
{
  uint anchor; // region begins
  uint focus;  // region ends, may less than anchor
  uint start;  // the small one in anchor & focus
  uint end;    // the big one in anchor & focus
  struct _phi_region *next;
} phi_region;

/*
 * Function: phi_region_new
 * ----------------------
 *   Create a new region with anchor & focus
 *
 *   returns: phi_region pointer
 */
phi_region *phi_region_new(uint anchor, uint focus);

/*
 * Function: phi_region_update
 * ----------------------
 *   Update a existing region with anchor & focus
 */
void phi_region_update(phi_region *region, uint anchor, uint focus);

/*
 * Function: phi_region_size
 * ----------------------
 *   Get a region's size
 *
 *   returns: the size from start to end
 */
uint phi_region_size(phi_region *region);

/*
 * Function: phi_region_empty
 * ----------------------
 *   Tell true if it's a empty region, just a cursor
 *
 *   returns: is region empty?
 */
bool phi_region_empty(phi_region *region);

/*
 * Function: phi_region_cover
 * ----------------------
 *   Combine 2 regions
 *
 *   returns: the final region combine with 2
 */
phi_region *phi_region_cover(phi_region *a, phi_region *b);

/*
 * Function: phi_region_intersection
 * ----------------------
 *   Get 2 regions' intersection
 *
 *   returns: the final intersection region
 */
phi_region *phi_region_intersection(phi_region *a, phi_region *b);

/*
 * Function: phi_region_intersects
 * ----------------------
 *   Tell if 2 regions' are intersects
 *
 *   returns: are they intersects?
 */
bool phi_region_intersects(phi_region *a, phi_region *b);

/*
 * Function: phi_region_contains
 * ----------------------
 *   Tell if region a contains region b
 *
 *   returns: Is regions a contains region b?
 */
bool phi_region_contains(phi_region *a, phi_region *b);

/*
 * Function: phi_region_contains_point
 * ----------------------
 *   Tell if region contains point
 *
 *   returns: Is region contains the point?
 */
bool phi_region_contains_point(phi_region *a, uint point);

#endif

