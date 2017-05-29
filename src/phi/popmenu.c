#include "popmenu.h"

PtkMenu *phi_popmenu_new() {
  PtkMenu     *editMenu   = ptk_popup_menu_new();
  PtkMenuItem *undoItem   = ptk_menu_item_new("Undo", NULL);
  PtkMenuItem *redoItem   = ptk_menu_item_new("Redo", NULL);
  PtkMenuItem *copyItem   = ptk_menu_item_new("Copy", NULL);
  PtkMenuItem *cutItem    = ptk_menu_item_new("Cut", NULL);
  PtkMenuItem *pasteItem  = ptk_menu_item_new("Paste", NULL);

  ptk_menu_shell_append(editMenu, undoItem);
  ptk_menu_shell_append(editMenu, redoItem);
  ptk_menu_shell_append(editMenu, ptk_menu_separator_new());
  ptk_menu_shell_append(editMenu, copyItem);
  ptk_menu_shell_append(editMenu, cutItem);
  ptk_menu_shell_append(editMenu, pasteItem);

  return editMenu;
}
