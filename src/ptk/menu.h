#ifndef __PTK_MENU__
#define __PTK_MENU__

#include <string.h>
#include "target/types.h"
#include "window.h"

PtkMenuBar       *ptk_menu_bar_new();
PtkMenu          *ptk_menu_new();
PtkMenu          *ptk_popup_menu_new();
PtkMenuItem      *ptk_menu_item_new(char name[], char shortcut[]);
PtkMenuSeparator *ptk_menu_separator_new();

void ptk_menu_bar_append(PtkMenuBar *menuBar, PtkMenuItem *menuItem);
void ptk_menu_shell_append(PtkMenu *menu, PtkMenuItem *menuItem);
void ptk_menu_item_set_submenu(PtkMenuItem *menuItem, PtkMenu *menu);
void ptk_menu_popup(PtkWindow *window, PtkMenu *menu, unsigned int time, int x, int y);

#endif
