#include "popmenu.h"

PtkMenu *phi_popmenu_new() {
  PtkMenu     *editMenu   = ptk_popup_menu_new();
  PtkMenuItem *undoItem   = ptk_menu_item_new("Undo");
  PtkMenuItem *redoItem   = ptk_menu_item_new("Redo");
  PtkMenuItem *copyItem   = ptk_menu_item_new("Copy");
  PtkMenuItem *cutItem    = ptk_menu_item_new("Cut");
  PtkMenuItem *pasteItem  = ptk_menu_item_new("Paste");

  ptk_menu_shell_append(editMenu, undoItem);
  ptk_menu_shell_append(editMenu, redoItem);
  ptk_menu_shell_append(editMenu, ptk_menu_separator_new());
  ptk_menu_shell_append(editMenu, copyItem);
  ptk_menu_shell_append(editMenu, cutItem);
  ptk_menu_shell_append(editMenu, pasteItem);

  return editMenu;
}
