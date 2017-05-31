#ifndef __PTK_MENU__
#define __PTK_MENU__

#include <stdlib.h>
#include <string.h>
#include "target/types.h"
#include "window.h"

/*
 * Function: ptk_accel_group_new
 * ----------------------
 *   Create a accelerator group for keyboard shortcuts
 *
 *   returns: PtkAccelGroup instance
 */
PtkAccelGroup *ptk_accel_group_new();
PtkMenuBar *ptk_menu_bar_new();
PtkMenu *ptk_menu_new();
PtkMenu *ptk_popup_menu_new();
PtkMenuItem *ptk_menu_item_new(char name[],
                               char shortcut[],
                               PtkAccelGroup *accel_group);
PtkMenuSeparator *ptk_menu_separator_new();

void ptk_menu_bar_append(PtkMenuBar *menuBar, PtkMenuItem *menuItem);
void ptk_menu_shell_append(PtkMenu *menu, PtkMenuItem *menuItem);
void ptk_menu_item_set_submenu(PtkMenuItem *menuItem, PtkMenu *menu);
void ptk_menu_popup(PtkWindow *window, PtkMenu *menu, uint time, int x, int y);

#endif
