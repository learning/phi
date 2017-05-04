#ifndef __PHI_WINDOW__
#define __PHI_WINDOW__

#include "../ptk/ptk.h"
#include "view.h"
#include "menubar.h"
#include "popmenu.h"

#define TITLE  "Phi"
#define WIDTH  400
#define HEIGHT 250

/*
 * Struct: PhiWindow
 * ---------------
 *   Represents a window, a phi instance can hold multiple views at a time.
 *   And many views in one window
 */
typedef struct phi_window_t {
  PtkWindow *ptk_window;
  PhiView *view_list;
  struct phi_window_t *next;
} PhiWindow;

/*
 * Function: phi_window_new
 * --------------------------
 *   Create a phi window
 *
 *   param: platform specify parameters
 */
PhiWindow *phi_window_new(PlatformParam param);

/*
 * Function: phi_window_add_view
 * --------------------------
 *   Add a view to the window
 *
 *   window: the window which contains the view
 *   buffer: the buffer which required to create the view
 */
void phi_window_add_view(PhiWindow *window, PhiBuffer *buffer);

#endif
