#include "../menu.h"

PtkAccelGroup *ptk_accel_group_new() {
  return NULL;
}

PtkMenuBar *ptk_menu_bar_new() {
  return CreateMenu();
}

PtkMenu *ptk_menu_new() {
  return CreateMenu();
}

PtkMenu *ptk_popup_menu_new() {
  return CreatePopupMenu();
}

PtkMenuItem *ptk_menu_item_new(char name[],
                               char shortcut[],
                               PtkAccelGroup *accel_group) {
  // convert '_' to '&'
  size_t nameLength = strlen(name);
  char *convertedName = (char *) malloc(nameLength + 1);
  for (int i = 0; i < nameLength; ++i) {
    if (name[i] == '_') {
      convertedName[i] = '&';
    } else {
      convertedName[i] = name[i];
    }
  }
  convertedName[nameLength] = '\0';
  wchar_t *text = new wchar_t[255];
  std::mbstowcs(text, convertedName, strlen(convertedName) + 1);
  PtkMenuItem *menuItem = (PtkMenuItem *) malloc(sizeof(PtkMenuItem));
  menuItem->name = text;
  menuItem->submenu = NULL;
  return menuItem;
}

PtkMenuSeparator *ptk_menu_separator_new() {
  PtkMenuSeparator *separator = (PtkMenuSeparator *) malloc(sizeof(PtkMenuSeparator));
  separator->name = NULL;
  separator->submenu = NULL;
  return separator;
}

void ptk_menu_bar_append(PtkMenuBar *menuBar, PtkMenuItem *menuItem) {
  AppendMenuW(menuBar, MF_POPUP,
    (UINT_PTR) menuItem->submenu, menuItem->name);
}

void ptk_menu_shell_append(PtkMenu *menu, PtkMenuItem *menuItem) {
  if (menuItem->name == NULL) {
    // separator
    AppendMenuW(menu, MF_SEPARATOR, 0, NULL);
  } else {
    if (menuItem->submenu == NULL) {
      // menu item
      AppendMenuW(menu, MF_STRING, 0, menuItem->name);
    } else {
      // submenu
      AppendMenuW(menu, MF_STRING | MF_POPUP,
        (UINT_PTR) menuItem->submenu, menuItem->name);
    }
  }
}

void ptk_menu_item_set_submenu(PtkMenuItem *menuItem, PtkMenu *menu) {
  menuItem->submenu = menu;
}

void ptk_menu_popup(PtkWindow *window, PtkMenu *menu, unsigned int time, int x, int y) {
  POINT point;
  point.x = x;
  point.y = y;
  ClientToScreen(window->instance, &point);
  TrackPopupMenu(menu, TPM_RIGHTBUTTON, point.x, point.y, 0, window->instance, NULL);
  DestroyMenu(menu);
}
