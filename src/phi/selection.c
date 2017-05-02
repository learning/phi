#include "selection.h"

/* <==== private functions ====> */
void _selection_clear_region_list(PhiSelection *selection) {
  PhiRegion *node;

  while((node = selection->region_list) != NULL) {
    selection->region_list = selection->region_list->next;
    free(node);
  }
}

PhiSelection *phi_selection_new() {
  PhiSelection *selection = (PhiSelection *) malloc(sizeof(PhiSelection));
  PhiRegion *region = phi_region_new(0, 0);
  selection->region_list = region;
  return selection;
}

void phi_selection_destroy(PhiSelection *selection) {
  _selection_clear_region_list(selection);
  free(selection);
}
