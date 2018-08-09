#ifndef __PHI_BACKEND_PANE__
#define __PHI_BACKEND_PANE__

#include "types.h"
#include "view.h"

typedef struct
{
  phi_view *views; // views in this pane
  phi_view *last_view;
} phi_pane;

/*
 * Function: phi_pane_new
 * ----------------------
 *   Create a new pane with views
 *
 *   returns: phi_pane pointer
 */
phi_pane *phi_pane_new(phi_view *views);

/*
 * Function: phi_pane_destroy
 * ----------------------
 *   Destroy a pane, there are 2 situations
 *     1. Just close the window & close all panes
 *     2. Change multiple panes to only one pane in a window,
 *        that a target pane will be passed into it.
 */
void phi_pane_destroy(phi_pane *pane, phi_pane *target_pane);

/*
 * Function: phi_pane_insert_view
 * ----------------------
 *   Insert view(s) to a pane, by index, -1 stand for append to the end
 */
void phi_pane_insert_view(phi_pane *pane, phi_view *view, int index);

/*
 * Function: phi_pane_create_view
 * ----------------------
 *   Create a view and insert it to the pane, by index,
 *   -1 stand for append to the end
 */
void phi_pane_create_view(phi_pane *pane, int index);

/*
 * Function: phi_pane_remove_view
 * ----------------------
 *   Remove a view from the pane, not destory, it maybe use for another pane
 */
void phi_pane_remove_view(phi_pane *pane, phi_view *view);

/*
 * Function: phi_pane_destroy_view
 * ----------------------
 *   Remove a view from the pane, and destory, stand for close the view
 */
void phi_pane_destroy_view(phi_pane *pane, phi_view *view);

#endif
