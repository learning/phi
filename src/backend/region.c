#include "region.h"

phi_region *phi_region_new(uint anchor, uint focus) {
  phi_region *region = (phi_region *) malloc(sizeof(region));
  phi_region_update(region, anchor, focus);
  region->next = NULL;
  return region;
}

void phi_region_update(phi_region *region, uint anchor, uint focus) {
  region->anchor = anchor;
  region->focus = focus;
  region->start = anchor < focus ? anchor : focus;
  region->end = anchor < focus ? focus : anchor;
}

uint phi_region_size(phi_region *region) {
  return region->end - region->start;
}

bool phi_region_empty(phi_region *region) {
  return region->anchor == region->focus;
}

phi_region *phi_region_cover(phi_region *a, phi_region *b) {
  uint start = a->start < b->start ? a->start : b->start;
  uint end = a->end > b->end ? a->end : b->end;
  return phi_region_new(start, end);
}

phi_region *phi_region_intersection(phi_region *a, phi_region *b) {
  uint start = a->start > b->start ? a->start : b->start;
  uint end = a->end < b->end ? a->end : b->end;
  return phi_region_new(start, end);
}

bool phi_region_intersects(phi_region *a, phi_region *b) {
  return (b->start > a->start && b->start < a->end) || // b->start inside a
         (b->end > a->start && b->end < a->end); // b->end inside a
}

bool phi_region_contains(phi_region *a, phi_region *b) {
  return a->start <= b->start && a->end >= b->end;
}

bool phi_region_contains_point(phi_region *a, uint point) {
  return a->start <= point && point <= a->end;
}
