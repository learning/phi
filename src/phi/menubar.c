#include "menubar.h"

PtkMenuBar *phi_menu_bar_init() {
  PtkMenuBar  *menuBar  = ptk_menu_bar_new();

  PtkMenuItem *fileItem = ptk_menu_item_new("File");
  PtkMenu     *fileMenu = ptk_menu_new();
  PtkMenuItem *newItem  = ptk_menu_item_new("New");
  PtkMenuItem *openItem = ptk_menu_item_new("Open");
  PtkMenuItem *quitItem = ptk_menu_item_new("Quit");

  PtkMenuItem *editItem   = ptk_menu_item_new("Edit");
  PtkMenu     *editMenu   = ptk_menu_new();
  PtkMenuItem *undoItem   = ptk_menu_item_new("Undo");
  PtkMenuItem *redoItem   = ptk_menu_item_new("Redo");
  PtkMenuItem *copyItem   = ptk_menu_item_new("Copy");
  PtkMenuItem *cutItem    = ptk_menu_item_new("Cut");
  PtkMenuItem *pasteItem  = ptk_menu_item_new("Paste");

  ptk_menu_item_set_submenu(fileItem, fileMenu);
  ptk_menu_shell_append(fileMenu, newItem);
  ptk_menu_shell_append(fileMenu, openItem);
  ptk_menu_shell_append(fileMenu, ptk_menu_separator_new());
  ptk_menu_shell_append(fileMenu, quitItem);

  ptk_menu_item_set_submenu(editItem, editMenu);
  ptk_menu_shell_append(editMenu, undoItem);
  ptk_menu_shell_append(editMenu, redoItem);
  ptk_menu_shell_append(editMenu, ptk_menu_separator_new());
  ptk_menu_shell_append(editMenu, copyItem);
  ptk_menu_shell_append(editMenu, cutItem);
  ptk_menu_shell_append(editMenu, pasteItem);

  ptk_menu_bar_append(menuBar, fileItem);
  ptk_menu_bar_append(menuBar, editItem);

  // ptk_add_event_listener(quitItem, PTK_EVENT_MENU_ACTIVATE, ptk_main_quit, NULL);

  return menuBar;
}
