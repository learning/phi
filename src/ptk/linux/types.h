#ifndef __PTK_TYPES__
#define __PTK_TYPES__

#include <gtk/gtk.h>

/* platform parameter */
typedef int PlatformParam;

/* menu */
typedef GtkWidget PtkMenuBar;
typedef GtkWidget PtkMenu;
typedef GtkWidget PtkMenuItem;
typedef GtkWidget PtkMenuSeparator;

/* window */
typedef struct {
  GtkWidget *gtk_window;
  GtkWidget *canvas;
  GtkIMContext *im_context;
} PtkWindow;

/* drawing */
typedef cairo_t PtkCanvas;

/* text */
typedef PangoLayout PtkTextLayout;

#endif
