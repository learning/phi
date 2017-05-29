#include <stdlib.h>
#include "menubar.h"

/* menu bar demo */
PhiMenuBar *phi_menu_bar_new() {
  PhiMenuBar *menuBar = (PhiMenuBar *) malloc(sizeof(PhiMenuBar));
  PtkMenuBar  *ptk_widget  = ptk_menu_bar_new();

  PtkMenuItem *fileItem = ptk_menu_item_new("_File", NULL);
  PtkMenu     *fileMenu = ptk_menu_new();
  PtkMenuItem *newItem  = ptk_menu_item_new("_New", "ctrl+n");
  PtkMenuItem *openItem = ptk_menu_item_new("_Open", "ctrl+o");
  PtkMenuItem *quitItem = ptk_menu_item_new("_Quit", "ctrl+q");

  PtkMenuItem *editItem   = ptk_menu_item_new("_Edit", NULL);
  PtkMenu     *editMenu   = ptk_menu_new();
  PtkMenuItem *undoItem   = ptk_menu_item_new("_Undo", "ctrl+z");
  PtkMenuItem *redoItem   = ptk_menu_item_new("_Redo", "ctrl+y");
  PtkMenuItem *copyItem   = ptk_menu_item_new("_Copy", "ctrl+c");
  PtkMenuItem *cutItem    = ptk_menu_item_new("Cut", "ctrl+x");
  PtkMenuItem *pasteItem  = ptk_menu_item_new("_Paste", "ctrl+v");

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

  ptk_menu_bar_append(ptk_widget, fileItem);
  ptk_menu_bar_append(ptk_widget, editItem);

  // ptk_add_event_listener(quitItem, PTK_EVENT_MENU_ACTIVATE, ptk_main_quit, NULL);
  menuBar->ptk_widget = ptk_widget;

  return menuBar;
}
