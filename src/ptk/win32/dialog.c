#include "../dialog.h"

void ptk_show_dialog(PtkWindow *window, char message[]) {
  MessageBox(
    window->instance,
    message,
    "Phi",
    MB_ICONQUESTION | MB_OK | MB_APPLMODAL
  );
}
