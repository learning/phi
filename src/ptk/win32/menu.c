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
  size_t nameLength, shortcutLength, resultLength;

  nameLength = strlen(name);

  if (shortcut == NULL) {
    // no shortcut, name + \0
    resultLength = nameLength + 1;
  } else {
    // has shortcut, name + \t + shortcut + \0
    shortcutLength = strlen(shortcut);
    resultLength = nameLength + shortcutLength + 2;
  }

  char *convertedName = (char *) malloc(resultLength);

  // convert '_' to '&'
  for (int i = 0; i < nameLength; ++i) {
    if (name[i] == '_') {
      convertedName[i] = '&';
    } else {
      convertedName[i] = name[i];
    }
  }

  // ...and merge shortcut into it, if it has one
  if (shortcut != NULL) {
    convertedName[nameLength] = '\t';
    // TODO: need shortcut Captialize
    for (int j = 0; j < shortcutLength; ++j) {
      convertedName[nameLength + j + 1] = shortcut[j];
    }
  }
  // add \0 to the end
  convertedName[resultLength - 1] = '\0';
  wchar_t *text = new wchar_t[255];
  std::mbstowcs(text, convertedName, strlen(convertedName) + 1);
  free(convertedName);
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
