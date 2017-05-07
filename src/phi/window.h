/*
 * phi/window.h
 *
 * A window of phi instance, an instance can hold multiple windows
 */
#ifndef __PHI_WINDOW__
#define __PHI_WINDOW__

#include "view.h"

typedef struct phi_window_t {
  PtkWindow *widget; // The actual window widget
  PhiView *views; // The views in this window
} PhiWindow;

/*
 * Function: phi_window_new
 * ----------------------
 *   Create a phi window
 *
 *   path: file path, optional
 */
PhiWindow *phi_window_new(char *path);

/*
 * Function: phi_window_destroy
 * ----------------------
 *   Destroy a phi window
 */
void phi_window_destroy();

#endif
