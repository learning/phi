#include "../menu.h"

PtkMenuBar *ptk_menu_bar_new() {
  PtkMenuBar *menuBar = gtk_menu_bar_new();
  gtk_widget_show(menuBar);
  return menuBar;
}

PtkMenu *ptk_menu_new() {
  PtkMenu *menu = gtk_menu_new();
  gtk_widget_show(menu);
  return menu;
}

PtkMenu *ptk_popup_menu_new() {
  return ptk_menu_new();
}

PtkMenuItem *ptk_menu_item_new(const char name[]) {
  PtkMenuItem *menuItem = gtk_menu_item_new_with_label(name);
  gtk_widget_show(menuItem);
  return menuItem;
}

PtkMenuSeparator *ptk_menu_separator_new() {
  PtkMenuSeparator *separator = gtk_separator_menu_item_new();
  gtk_widget_show(separator);
  return separator;
}

void ptk_menu_bar_append(PtkMenuBar *menuBar, PtkMenuItem *menuItem) {
  gtk_menu_bar_append(GTK_MENU_BAR(menuBar), menuItem);
}

void ptk_menu_shell_append(PtkMenu *menu, PtkMenuItem *menuItem) {
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);
}

void ptk_menu_item_set_submenu(PtkMenuItem *menuItem, PtkMenu *menu) {
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
}

void ptk_menu_popup(PtkWindow *window, PtkMenu *menu, unsigned int time, int x, int y) {
  gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 3, time);
}
