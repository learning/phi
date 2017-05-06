#ifndef __PHI_WINDOW__
#define __PHI_WINDOW__

typedef struct phi_window_t {
  PtkWindow *widget; // The actual window widget
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
