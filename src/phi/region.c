#include "region.h"

PhiRegion *phi_region_new(int begin, int end) {
  PhiRegion *region = (PhiRegion *) malloc(sizeof(PhiRegion));
  return region;
}

void phi_region_destroy(PhiRegion *region) {
  free(region);
}
