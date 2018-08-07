#ifndef __PHI_BACKEND_WINDOW__
#define __PHI_BACKEND_WINDOW__

#include "types.h"
#include "pane.h"

#define MAX_PANES 4

typedef struct _phi_window
{
  phi_pane *panes[MAX_PANES];
} phi_window;

#endif
