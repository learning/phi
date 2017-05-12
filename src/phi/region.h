/*
 * phi/region.h
 *
 * Represent a text region in a text view
 */
#ifndef __PHI_REGION__
#define __PHI_REGION__

typedef struct phi_region_t {
  unsigned int start_pos; // The start position of region
  unsigned int end_pos; // The end position of region
  struct phi_region_t *next; // So, it's a linked list
} PhiRegion;

/*
 * Function: phi_region_new
 * ----------------------
 *   Create a region for view
 *
 *   start_pos: the start position of text in the view
 *   end_pos: the end position of text in the view
 */
PhiRegion *phi_region_new(unsigned int start_pos, unsigned int end_pos);

/*
 * Function: phi_region_destroy
 * ----------------------
 *   Destroy a phi region
 *
 *   region: the region of the view
 */
void phi_region_destroy(PhiRegion *region);

#endif
