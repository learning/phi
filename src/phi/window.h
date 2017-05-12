/*
 * phi/window.h
 *
 * A window of phi instance, an instance can hold multiple windows
 */
#ifndef __PHI_WINDOW__
#define __PHI_WINDOW__

#include "../ptk/ptk.h"
#include "view.h"
#include "menubar.h"

#define TITLE "Phi"
#define WIDTH 400
#define HEIGHT 250

typedef struct phi_window_t {
  PtkWindow *ptk_widget; // The actual window widget
  PhiMenuBar *menu_bar;
  PhiView *view_list; // The views in this window

  struct phi_window_t *next;
} PhiWindow;

/*
 * Function: phi_window_new
 * ----------------------
 *   Create a phi window
 *
 *   path: file path, optional
 *   param: platform specified parameter
 */
PhiWindow *phi_window_new(char *path, PlatformParam param);

/*
 * Function: phi_window_destroy
 * ----------------------
 *   Destroy a phi window
 */
void phi_window_destroy(PhiWindow *window);

#endif
