#ifndef __PTK_WINDOW__
#define __PTK_WINDOW__

#include "target/types.h"

/*
 * Enum: PtkButtonType
 * ----------------------
 *   Enum for mouse buttons
 */
typedef enum {
  PTK_BUTTON_UNKNOWN = 0,
  PTK_BUTTON_LEFT,
  PTK_BUTTON_MIDDLE,
  PTK_BUTTON_RIGHT
} PtkButtonType;

/*
 * Function: ptk_window_new
 * ----------------------
 *   Create a window instance with specify width and height
 *
 *   returns: PtkWindow instance
 */
PtkWindow *ptk_window_new(int width, int height, PtkMenuBar *menuBar, PlatformParam param);

/*
 * Function: ptk_window_set_title
 * ----------------------
 *   Set title for the PtkWindow
 */
void ptk_window_set_title(PtkWindow *window, const char title[]);

/*
 * Function: ptk_window_set_drawing_callback
 * ----------------------
 *   Set drawing callback for the PtkWindow
 */
void ptk_window_set_drawing_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkCanvas *, int, int));
void ptk_window_set_button_press_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkButtonType, unsigned int, int, int));
void ptk_window_set_button_release_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkButtonType, unsigned int, int, int));
void ptk_window_set_input_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, const char *));
// void ptk_window_set_key_press_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, int, int, int));
// void ptk_window_set_key_release_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, int, int, int));

#endif
