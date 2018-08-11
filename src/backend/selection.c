#include "selection.h"

uint selection_id = 1;

phi_selection *phi_selection_new(phi_region *regions) {
  phi_selection *selection = (phi_selection *) malloc(sizeof(phi_selection));
  selection->id = selection_id++;
  if (regions == NULL) {
    // Empty, start with one region (0, 0)
    selection->regions = phi_region_new(0, 0);
    selection->last_region = selection->regions;
  } else {
    // Set to regions, and find the last region
    selection->regions = regions;
    selection->last_region = selection->regions;
    while (selection->last_region->next != NULL) {
      selection->last_region = selection->last_region->next;
    }
  }
  return selection;
}

void phi_selection_destroy(phi_selection *selection) {
  if (selection == NULL) return;
  // Clear all regions first
  phi_selection_clear(selection);
  // And then destroy selection itself
  free(selection);
}

void phi_selection_clear(phi_selection *selection) {
  if (selection == NULL) return;

  phi_region *region = selection->regions;
  while (region != NULL) {
    selection->regions = region->next;
    phi_region_destroy(region);
    region = selection->regions;
  }
  selection->last_region = NULL;
}

void phi_selection_add(phi_selection *selection, phi_region *region) {
  if (selection == NULL || region == NULL) return;

  // Detect intersects of every existing regions
  phi_region *prev = NULL;
  phi_region *cursor = selection->regions;
  phi_region *tmp = NULL;
  while (cursor != NULL) {
    if (phi_region_intersects(region, cursor)) {
      // combine them
      tmp = phi_region_cover(region, cursor);
      // replace region
      phi_region_destroy(region);
      region = tmp;

      // destroy cursor
      if (prev == NULL) {
        // first region
        selection->regions = cursor->next;
      } else {
        // region in the middle
        prev->next = cursor->next;
      }
      // tmp released
      tmp = cursor->next;
      phi_region_destroy(cursor);
      cursor = tmp;
    } else {
      prev = cursor;
      cursor = cursor->next;
    }
  }

  selection->last_region->next = region;
  while (selection->last_region->next != NULL) {
    selection->last_region = selection->last_region->next;
  }
}

void phi_selection_remove(phi_selection *selection, phi_region *region) {
  if (region == NULL) return;

  phi_region *prev_region = NULL;
  phi_region *current_region = selection->regions;

  // find the region
  while (current_region != NULL && current_region != region) {
    prev_region = current_region;
    current_region = current_region->next;
  }

  if (current_region == region) {
    // re-link & destroy
    prev_region->next = region->next;
    phi_region_destroy(region);
  }
}

bool phi_selection_contains(phi_selection *selection, phi_region *region) {
  if (selection == NULL || region == NULL) return false;

  bool result = false;

  phi_region *current_region = selection->regions;

  while (current_region != NULL && !result) {
    if (current_region->anchor == region->anchor &&
        current_region->focus == region->focus) {
      // Found it
      result = true;
    } else {
      current_region = current_region->next;
    }
  }

  return result;
}
