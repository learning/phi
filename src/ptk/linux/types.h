#ifndef __PTK_TYPES__
#define __PTK_TYPES__

#include <gtk/gtk.h>

/* platform */
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

typedef cairo_t PtkCanvas;
typedef PangoLayout PtkTextLayout;

#endif
