#include "../dialog.h"

void ptk_show_dialog(PtkWindow *window, char message[]) {
  NSLog(@"ptk_show_dialog");
  NSAlert *alert = [NSAlert alertWithMessageText:@""
                            defaultButton:@"OK" alternateButton:nil otherButton:nil
                            informativeTextWithFormat:@"%s", message];
  [alert runModal];
  [alert release];
}
