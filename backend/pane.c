#include "pane.h"

uint pane_id = 1;

phi_pane *phi_pane_new(phi_view *views) {
  phi_pane *pane = (phi_pane *) malloc(sizeof(phi_pane));
  pane->id = pane_id++;
  pane->views = views;
  pane->last_view = views;
  while (pane->last_view != NULL && pane->last_view->next != NULL) {
    pane->last_view = pane->last_view->next;
  }

  return pane;
}

void phi_pane_destroy(phi_pane *pane, phi_pane *target_pane) {
  if (pane == NULL) return;

  if (target_pane != NULL) {
    phi_pane_insert_view(target_pane, pane->views, -1); // To the end
  } else {
    // destroy all views
    phi_view *view;
    while (pane->views != NULL) {
      view = pane->views;
      pane->views = view->next;
      phi_view_destroy(view);
    }
  }

  free(pane);
}

void phi_pane_insert_view(phi_pane *pane, phi_view *view, int index) {
  if (pane == NULL || view == NULL) return;

  phi_view *last_view = view;
  int i;
  phi_view *cursor;

  while (last_view->next != NULL) {
    last_view = last_view;
  }

  switch (index) {
    case -1: // To the end
      pane->last_view->next = view;
      pane->last_view = last_view;
      break;
    case 0: // To the head
      last_view->next = pane->views;
      pane->views = view;
      break;
    default: // To the middle
      i = 1;
      cursor = pane->views;
      while (i < index && cursor->next != NULL) {
        cursor = cursor->next;
        ++i;
      }
      if (pane->last_view == cursor) {
        // Append to the end, just like case -1
        pane->last_view->next = view;
        pane->last_view = last_view;
      } else {
        // In the middle
        last_view->next = cursor->next;
        cursor->next = view;
      }
      break;
  }
}

void phi_pane_create_view(phi_pane *pane, int index) {
  if (pane == NULL) return;

  phi_view *view = phi_view_new(NULL); // without filename
  phi_pane_insert_view(pane, view, index);
}

void phi_pane_remove_view(phi_pane *pane, phi_view *view) {
  if (pane == NULL || view == NULL) return;

  phi_view *cursor = pane->views;
  while (cursor != NULL && cursor->next != view) {
    cursor = cursor->next;
  }

  if (cursor != NULL && cursor->next == view) {
    cursor->next = view->next;
  }
}

void phi_pane_destroy_view(phi_pane *pane, phi_view *view) {
  if (pane == NULL || view == NULL) return;

  phi_pane_remove_view(pane, view);
  phi_view_destroy(view);
}
