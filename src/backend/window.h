#ifndef __PHI_BACKEND_WINDOW__
#define __PHI_BACKEND_WINDOW__

#include "types.h"
#include "pane.h"

#define MAX_PANES 4

typedef enum
{
  SINGLE,
  COLUMN_2,
  COLUMN_3,
  COLUMN_4,
  ROW_2,
  ROW_3,
  GRID_4,
  NUMBER_OF_LAYOUTS
} phi_layout;

typedef struct _phi_window
{
  uint id;
  phi_pane **panes;
  phi_layout layout;
} phi_window;

phi_window *phi_window_new();
void phi_window_destroy(phi_window *window);
void phi_window_change_layout(phi_window *window, phi_layout layout);

#endif
