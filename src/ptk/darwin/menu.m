#include "../menu.h"

// map string to int: http://bit.ly/2ryfPEE
// mainly the same as ptk linux

// key struct to store a key
struct key {
  char *name;
  int value;
};

// modifiers for macOS
struct key modifiers[] = {
  "alt", NSAlternateKeyMask,
  "ctrl", NSControlKeyMask,
  "shift", NSShiftKeyMask,
  "super", NSCommandKeyMask
};

// a compare function for binary search
int compare(const void *s1, const void *s2) {
  const struct key *k1 = s1;
  const struct key *k2 = s2;

  return strcmp(k1->name, k2->name);
}

PtkAccelGroup *ptk_accel_group_new() {
  NSLog(@"ptk_accel_group_new()");
  return NULL;
}

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

PtkMenuItem *ptk_menu_item_new(char name[], char shortcut[], PtkAccelGroup *accel_group) {
  NSString *_name = [NSString stringWithFormat:@"%s", name];
  PtkMenuItem *menuItem = [NSMenuItem new];
  [menuItem setTitle:_name];
  if (shortcut != NULL) {
    int modifier = 0;

    // get the first key token
    // have to use strdup to copy the string, or it cause segmentation fault
    // http://bit.ly/2siN0ZX
    char *token = strtok(strdup(shortcut), "+");
    NSString *key;

    while (token != NULL) {
      // find key value in modifiers
      struct key *result, find = { token, 0 };
      result = bsearch(&find, modifiers,
                       sizeof(modifiers) / sizeof(modifiers[0]),
                       sizeof(modifiers[0]), compare);
      if (result == NULL) {
        // it's the key, not modifier
        key = [NSString stringWithFormat:@"%s", token];
        break;
      } else {
        // it's the modifier
        modifier = modifier | result->value;
      }
      // get the next token
      token = strtok(NULL, "+");
    }

    [menuItem setKeyEquivalentModifierMask: modifier];
    [menuItem setKeyEquivalent:key];
  }
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
