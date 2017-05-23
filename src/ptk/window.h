#ifndef __PTK_WINDOW__
#define __PTK_WINDOW__

#include "target/types.h"

typedef unsigned int uint;

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
 * Callbacks
 */
typedef void (*WindowDrawCallback)(PtkWindow *, PtkCanvas *, int, int);
typedef void (*MousePressCallback)(PtkWindow *, PtkButtonType, uint, int, int);
typedef void (*MouseReleaseCallback)(PtkWindow *, PtkButtonType, uint, int, int);
typedef void (*KeyboardInputCallback)(PtkWindow *, const char *);

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
void ptk_window_set_drawing_callback(PtkWindow *window, WindowDrawCallback callback);

/*
 * Function: ptk_window_set_button_press_callback
 * ----------------------
 *   Set mouse button press callback for the PtkWindow
 */
void ptk_window_set_button_press_callback(PtkWindow *window, MousePressCallback callback);

/*
 * Function: ptk_window_set_button_release_callback
 * ----------------------
 *   Set mouse button release callback for the PtkWindow
 */
void ptk_window_set_button_release_callback(PtkWindow *window, MouseReleaseCallback callback);

/*
 * Function: ptk_window_set_input_callback
 * ----------------------
 *   Set text input callback for the PtkWindow
 */
void ptk_window_set_input_callback(PtkWindow *window, KeyboardInputCallback callback);

#endif
