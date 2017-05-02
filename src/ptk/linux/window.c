#include <stdlib.h>
#include <string.h>
#include "../window.h"
#include "../pevent.h"

typedef struct {
  PtkWindow *window;
  void *callback;
} CallbackData;

static gboolean _window_close_callback(GtkWidget *widget,
                                       GdkEvent *event,
                                       gpointer data) {
  PtkEvent evt = { "window_close" };
  ptk_dispatch(PTK_WINDOW_CLOSE, evt);
  return TRUE;
}

static gboolean _window_focus_callback(GtkWidget *widget,
                                       GdkEvent *event,
                                       PtkWindow *window) {
  gtk_widget_grab_focus(window->canvas);
  gtk_im_context_focus_in(window->im_context);
  gtk_im_context_reset(window->im_context);
  return TRUE;
}

static gboolean _window_blur_callback(GtkWidget *widget,
                                      GdkEvent *event,
                                      gpointer data) {
  return TRUE;
}

static gboolean _expose_event_callback(GtkWidget *widget,
                                       GdkEvent *event,
                                       gpointer data) {
  // widget is canvas, and data is callback function
  PtkCanvas *canvas = gdk_cairo_create(widget->window);
  ((void (*)(PtkCanvas *, int, int)) data)(canvas, widget->allocation.width,
                                                   widget->allocation.height);
  cairo_destroy(canvas);
  return TRUE;
}


static gboolean _button_press_event_callback(GtkWidget *widget,
                                             GdkEventButton *event,
                                             gpointer data) {
  // PtkWindow window = { NULL };
  // ((void (*)(PtkWindow, PtkButtonType, unsigned int, int, int)) data)(window, event->button, event->time, event->x, event->y);
  return TRUE;
}

static gboolean _button_release_event_callback(GtkWidget *widget,
                                             GdkEventButton *event,
                                             gpointer data) {
  // PtkWindow window = { NULL };
  // ((void (*)(PtkWindow, PtkButtonType, unsigned int, int, int)) data)(window, event->button, event->time, event->x, event->y);
  return TRUE;
}

static gboolean _key_press_event_callback(GtkWidget *widget,
                                          GdkEventKey *event,
                                          PtkWindow *window) {
  // PtkWindow window = { NULL, widget };
  // ((void (*)(PtkWindow *, int, int, int)) data)(window, event->keyval, event->state, event->is_modifier);
  // printf("_key_press_event_callback.\n");
  return gtk_im_context_filter_keypress(window->im_context, event);
}

// static gboolean _key_release_event_callback(GtkWidget *widget,
//                                             GdkEventKey *event,
//                                             gpointer data) {
//   PtkWindow window = { NULL, widget };
//   ((void (*)(PtkWindow *, int, int, int)) data)(window, event->keyval, event->state, event->is_modifier);
//   return TRUE;
// }

static void _im_commit_callback(GtkIMContext *context,
                                const gchar *str,
                                CallbackData *data) {
  ((void (*)(PtkWindow *, const char *)) data->callback)(data->window, str);
}

static void _im_preedit_changed_callback(GtkIMContext *context, PtkWindow *window) {
  printf("_im_preedit_changed_callback.\n");
}

static gboolean _im_retrieve_surrounding_callback(GtkIMContext *context, PtkWindow *window) {
  printf("_im_retrieve_surrounding_callback.\n");
  // gchar *text = "char";
  // gtk_im_context_set_surrounding (context, text, strlen (text), /* Length in bytes */
  //         g_utf8_offset_to_pointer(text, 0) - text);
  // g_free (text);

  return TRUE;
}

static gboolean _im_delete_surrounding_callback(GtkIMContext *context, gint offset, gint n_chars, PtkWindow *window) {
  printf("_im_delete_surrounding_callback: offset=%d, n_chars=%d\n.", offset, n_chars);
  return TRUE;
}

PtkWindow *ptk_window_new(int width, int height, PtkMenuBar *menuBar, PlatformParam param) {
  GtkWidget *gtk_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(gtk_window));
  GtkIMContext *im_context = gtk_im_multicontext_new();
  gtk_im_context_set_client_window(im_context, gdk_window);
  gtk_widget_show(gtk_window);

  /* init drawing area */
  GtkWidget *canvas = gtk_drawing_area_new();
  gtk_widget_set_can_focus(canvas, TRUE);
  gtk_widget_add_events(canvas, GDK_BUTTON_PRESS_MASK |
                                GDK_BUTTON_RELEASE_MASK |
                                GDK_KEY_PRESS_MASK |
                                GDK_KEY_RELEASE_MASK);
  gtk_widget_set_size_request(canvas, width, height);
  gtk_widget_show(canvas);

  if (menuBar == NULL) {
    gtk_container_add(GTK_CONTAINER(gtk_window), canvas);
  } else {
    GtkWidget *box = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(box);
    gtk_container_add(GTK_CONTAINER(gtk_window), box);
    gtk_box_pack_start(GTK_BOX(box), menuBar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), canvas, TRUE, TRUE, 0);
  }

  PtkWindow *window = malloc(sizeof(PtkWindow));
  window->gtk_window = gtk_window;
  window->canvas = canvas;
  window->im_context = im_context;

  g_signal_connect(gtk_window, "focus-in-event",
      G_CALLBACK(_window_focus_callback), window);
  g_signal_connect(gtk_window, "focus-out-event",
      G_CALLBACK(_window_blur_callback), NULL);
  g_signal_connect(gtk_window, "destroy",
      G_CALLBACK(_window_close_callback), NULL);
  g_signal_connect(canvas, "key-press-event",
      G_CALLBACK(_key_press_event_callback), window);
  // g_signal_connect(im_context, "commit",
  //     G_CALLBACK(_im_commit_callback), window);
  // g_signal_connect(im_context, "preedit-changed",
  //     G_CALLBACK(_im_preedit_changed_callback), window);
  // g_signal_connect(im_context, "retrieve-surrounding",
  //     G_CALLBACK(_im_retrieve_surrounding_callback), window);
  // g_signal_connect(im_context, "delete-surrounding",
  //     G_CALLBACK(_im_delete_surrounding_callback), window);

  return window;
}

void ptk_window_set_title(PtkWindow *window, const char title[]) {
  gtk_window_set_title(GTK_WINDOW(window->gtk_window), title);
}

void ptk_window_set_drawing_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkCanvas *, int, int)) {
  g_signal_connect(G_OBJECT(window->canvas), "expose_event",
      G_CALLBACK(_expose_event_callback), fpointer);
}

void ptk_window_set_button_press_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkButtonType, unsigned int, int, int)) {
  g_signal_connect(G_OBJECT(window->canvas), "button_press_event",
       G_CALLBACK(_button_press_event_callback), fpointer);
}

void ptk_window_set_button_release_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkButtonType, unsigned int, int, int)) {
  g_signal_connect(G_OBJECT(window->canvas), "button_release_event",
      G_CALLBACK(_button_release_event_callback), fpointer);
}

void ptk_window_set_input_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, const char *)) {
  CallbackData *data = malloc(sizeof(CallbackData));
  data->callback = fpointer;
  data->window = window;
  g_signal_connect(window->im_context, "commit",
      G_CALLBACK(_im_commit_callback), data);
}
// void ptk_window_set_key_press_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, int, int, int)) {
//   g_signal_connect(G_OBJECT(window->canvas), "key_press_event",
//       G_CALLBACK(_key_press_event_callback), fpointer);
// }

// void ptk_window_set_key_release_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, int, int, int)) {
//   g_signal_connect(G_OBJECT(window->canvas), "key_release_event",
//       G_CALLBACK(_key_release_event_callback), fpointer);
// }
