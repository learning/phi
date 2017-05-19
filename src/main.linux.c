#include <gtk/gtk.h>
#include "phi/app.h"

/*
 * The main entry point on linux
 */
int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // initialize phi
  phi_init(0);

  gtk_main();
  return 0;
}
