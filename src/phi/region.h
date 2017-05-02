#ifndef __PHI_REGION__
#define __PHI_REGION__

#include <stdlib.h>

typedef struct phi_region_t {
  unsigned int begin;
  unsigned int end;
  struct phi_region_t *next;
} PhiRegion;

/*
 * Function: phi_region_new
 * ------------------------
 *   Create a new region and return it.
 *
 *   begin: the begin index of this region
 *   end: the end index of this region
 *
 *   returns: the new region just create
 */
PhiRegion *phi_region_new(int begin, int end);

/*
 * Function: phi_region_destroy
 * ----------------------------
 *   Destroy a region
 *
 *   region: which region to be destroy
 */
void phi_region_destroy(PhiRegion *region);

#endif
