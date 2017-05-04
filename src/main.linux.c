#include <gtk/gtk.h>
#include "phi/app.h"

int main(int argc, char *argv[]) {
  GtkWidget *window;

  gtk_init(&argc, &argv);

  phi_init(0);

  gtk_main();
  return 0;
}
