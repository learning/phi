#include "../dialog.h"

void ptk_show_dialog(PtkWindow *window, char message[]) {
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(window->gtk_window),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_OK,
                                  message);
  // gtk_window_set_title(GTK_WINDOW(dialog), "Information");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
