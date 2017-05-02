#include "../menu.h"

PtkMenuBar *ptk_menu_bar_new() {
  PtkMenuBar *menuBar = [NSMenu new];
  return menuBar;
}

PtkMenu *ptk_menu_new() {
  PtkMenu *menu = [NSMenu new];
  return menu;
}

PtkMenu *ptk_popup_menu_new() {
  return ptk_menu_new();
}

PtkMenuItem *ptk_menu_item_new(const char name[]) {
  NSString *_name = [NSString stringWithFormat:@"%s", name];
  PtkMenuItem *menuItem = [NSMenuItem new];
  [menuItem setTitle:_name];
  return menuItem;
}

PtkMenuSeparator *ptk_menu_separator_new() {
  PtkMenuSeparator *separator = [NSMenuItem separatorItem];
  return separator;
}

void ptk_menu_bar_append(PtkMenuBar *menuBar, PtkMenuItem *menuItem) {
  [menuBar addItem:menuItem];
}

void ptk_menu_shell_append(PtkMenu *menu, PtkMenuItem *menuItem) {
  [menu addItem:menuItem];
}

void ptk_menu_item_set_submenu(PtkMenuItem *menuItem, PtkMenu *menu) {
  [menu setTitle:menuItem.title];
  [menuItem setSubmenu:menu];
}

void ptk_menu_popup(PtkWindow *window, PtkMenu *menu, unsigned int time, int x, int y) {
  [menu popUpMenuPositioningItem:nil atLocation:CGPointMake(x, y) inView:window->view];
}
