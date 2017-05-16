/*
 * phi/menubar.h
 *
 * The menu bar of a window
 */
#ifndef __PHI_MENUBAR__
#define __PHI_MENUBAR__

#include "../ptk/ptk.h"

typedef struct phi_menu_bar_t {
  PtkMenuBar *ptk_widget;
} PhiMenuBar;

/*
 * Function: phi_menu_bar_new
 * ----------------------
 *   Create a menu bar for window
 */
PhiMenuBar *phi_menu_bar_new();

#endif
