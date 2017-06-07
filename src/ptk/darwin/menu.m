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

struct key keymap[] = {
  "backspace", '\b',
  "delete", NSDeleteFunctionKey,
  "down", NSDownArrowFunctionKey,
  "end", NSEndFunctionKey,
  "enter", '\r',
  "esc", '\e',
  "f1", NSF1FunctionKey,
  "f10", NSF10FunctionKey, /* f10 - f12 is behind f1, or bsearh will failed */
  "f11", NSF11FunctionKey,
  "f12", NSF12FunctionKey,
  "f2", NSF2FunctionKey,
  "f3", NSF3FunctionKey,
  "f4", NSF4FunctionKey,
  "f5", NSF5FunctionKey,
  "f6", NSF6FunctionKey,
  "f7", NSF7FunctionKey,
  "f8", NSF8FunctionKey,
  "f9", NSF9FunctionKey,
  "home", NSHomeFunctionKey,
  "insert", NSInsertFunctionKey,
  "keypad_enter", '\r',
  "left", NSLeftArrowFunctionKey,
  "pagedown", NSPageDownFunctionKey,
  "pageup", NSPageUpFunctionKey,
  "right", NSRightArrowFunctionKey,
  "tab", '\t',
  "up", NSUpArrowFunctionKey,
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
    int key = 0;
    NSString *_key;

    // get the first key token
    // have to use strdup to copy the string, or it cause segmentation fault
    // http://bit.ly/2siN0ZX
    char *token = strtok(strdup(shortcut), "+");

    // if key is not 0, stop the loop
    while (key == 0 && token != NULL) {
      if (strlen(token) > 1) {
        // find key value in modifiers
        struct key *result, find = { token, 0 };
        result = bsearch(&find, modifiers,
                         sizeof(modifiers) / sizeof(modifiers[0]),
                         sizeof(modifiers[0]), compare);
        if (result == NULL) {
          // it's the key, not modifier
          key = [NSString stringWithFormat:@"%s", token];
          result = bsearch(&find, keymap, sizeof(keymap) / sizeof(keymap[0]),
                           sizeof(keymap[0]), compare);
          if (result == NULL) {
            printf("key unknown: %s\n", token);
          } else {
            unichar ch[4];
            ch[0] = result->value;
            _key = [NSString stringWithCharacters:ch length:1];
            key = result->value;
          }
          break;
        } else {
          // it's the modifier
          modifier = modifier | result->value;
        }
      } else {
        _key = [NSString stringWithFormat:@"%s", token];
        key = token[0];
      }
      // get the next token
      token = strtok(NULL, "+");
    }


    [menuItem setKeyEquivalentModifierMask: modifier];
    [menuItem setKeyEquivalent:_key];
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
