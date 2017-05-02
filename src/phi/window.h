#ifndef __PHI_WINDOW__
#define __PHI_WINDOW__

#include "../ptk/ptk.h"
#include "view.h"
#include "menubar.h"
#include "popmenu.h"

#define TITLE  "Phi"
#define WIDTH  400
#define HEIGHT 250

typedef struct phi_window_t {
  PtkWindow *ptk_window;
  PhiView *view_list;
  struct phi_window_t *next;
} PhiWindow;

PhiWindow *phi_window_new(PlatformParam param);
void phi_window_add_view(PhiWindow *window, PhiBuffer *buffer);

#endif
