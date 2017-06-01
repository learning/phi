#include <gdk/gdkkeysyms.h>
#include "../menu.h"

// map string to int: http://bit.ly/2ryfPEE

// key struct to store a key
struct key {
  char *name;
  int value;
};

// modifiers for linux 
struct key modifiers[] = {
  "alt", GDK_MOD1_MASK,
  "ctrl", GDK_CONTROL_MASK,
  "shift", GDK_SHIFT_MASK,
  "super", GDK_SUPER_MASK
};

// keymap for linux, store multiple characters named keys only
struct key keymap[] = {
  "backspace", GDK_KEY_BackSpace,
  "delete", GDK_KEY_Delete,
  "down", GDK_KEY_Down,
  "end", GDK_KEY_End,
  "enter", GDK_KEY_Return,
  "esc", GDK_KEY_Escape,
  "f1", GDK_KEY_F1,
  "f10", GDK_KEY_F10, /* f10 - f12 is behind f1, or bsearh will failed */
  "f11", GDK_KEY_F11,
  "f12", GDK_KEY_F12,
  "f2", GDK_KEY_F2,
  "f3", GDK_KEY_F3,
  "f4", GDK_KEY_F4,
  "f5", GDK_KEY_F5,
  "f6", GDK_KEY_F6,
  "f7", GDK_KEY_F7,
  "f8", GDK_KEY_F8,
  "f9", GDK_KEY_F9,
  "home", GDK_KEY_Home,
  "insert", GDK_KEY_Insert,
  "keypad_enter", GDK_KEY_KP_Enter,
  "left", GDK_KEY_Left,
  "pagedown", GDK_KEY_Page_Down,
  "pageup", GDK_KEY_Page_Up,
  "right", GDK_KEY_Right,
  "tab", GDK_KEY_Tab,
  "up", GDK_KEY_Up,
};

// a compare function for binary search
int compare(const void *s1, const void *s2) {
  const struct key *k1 = s1;
  const struct key *k2 = s2;

  return strcmp(k1->name, k2->name);
}

PtkAccelGroup *ptk_accel_group_new() {
  return gtk_accel_group_new();
}

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

PtkMenuItem *ptk_menu_item_new(char name[],
                               char shortcut[],
                               PtkAccelGroup *accel_group) {
  PtkMenuItem *menuItem = gtk_menu_item_new_with_mnemonic(name);
  printf("process: %s\n", shortcut);
  if (shortcut != NULL) {
    // split the combine key string: http://bit.ly/2sGeFqC
    int modifier = 0;
    int key = 0;
    // get the first key token
    // have to use strdup to copy the string, or it cause segmentation fault
    // http://bit.ly/2siN0ZX
    char *token = strtok(strdup(shortcut), "+");

    // if key is not null, stop the loop
    while (key == 0 && token != NULL) {
      if (strlen(token) > 1) {
        // find key value in modifiers & keymap
        struct key *result, find = { token, 0 };
        result = bsearch(&find, modifiers,
                         sizeof(modifiers) / sizeof(modifiers[0]),
                         sizeof(modifiers[0]), compare);
        if (result == NULL) {
          result = bsearch(&find, keymap, sizeof(keymap) / sizeof(keymap[0]),
                           sizeof(keymap[0]), compare);
          if (result == NULL) {
            printf("key unknown: %s\n", token);
          } else {
            key = result->value;
            printf("  key: %s, value: %d\n", result->name, result->value);
          }
        } else {
          printf("  modifier: %s, value: %d\n", result->name, result->value);
          modifier = modifier | result->value;
        }
      } else {
        printf("  key: %c, value: %d\n", token[0], token[0]);
        key = token[0];
      }
      // get the next token
      token = strtok(NULL, "+");
    }

    if (key == 0) {
    } else {
      gtk_widget_add_accelerator(menuItem, "activate", accel_group,
                key, modifier, GTK_ACCEL_VISIBLE);
    }
  }
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

void ptk_menu_popup(PtkWindow *window, PtkMenu *menu, uint time, int x, int y) {
  gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 3, time);
}
