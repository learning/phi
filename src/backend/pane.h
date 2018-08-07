#ifndef __PHI_BACKEND_PANE__
#define __PHI_BACKEND_PANE__

#include "types.h"
#include "view.h"

typedef struct
{
  phi_view *views; // views in this pane
  phi_view *last_view;
} phi_pane;

phi_pane *phi_pane_new(phi_view *views);
void phi_pane_destroy(phi_pane *pane);
void phi_pane_insert_view(phi_pane *pane, phi_view *view, int index);
void phi_pane_create_view(phi_pane *pane, int index);
void phi_pane_remove_view(phi_pane *pane, phi_view *view);
void phi_pane_destroy_view(phi_pane *pane, phi_view *view);

#endif
