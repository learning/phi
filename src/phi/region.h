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

#endif
