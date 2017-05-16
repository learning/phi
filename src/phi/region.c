#include "region.h"

PhiRegion *phi_region_new(unsigned int start_pos, unsigned int end_pos) {
  PhiRegion *region = (PhiRegion *) malloc(sizeof(PhiRegion));

  region->start_pos = start_pos;
  region->end_pos = end_pos;

  return region;
}

void phi_region_destroy(PhiRegion *region) {
  free((void *) region);
}
