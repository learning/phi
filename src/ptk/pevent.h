#ifndef __PTK_EVENT__
#define __PTK_EVENT__

/*
 * Enum: PtkEventType
 * ----------------------
 *   Enum for event types
 */
typedef enum {
  PTK_WINDOW_CLOSE,
  PTK_MENU_ACTIVATE,

  // Count event types' number
  NUMBER_OF_EVENTS
} PtkEventType;

/*
 * Struct: PtkEvent
 * ----------------------
 *   Struct for the event
 */
typedef struct {
  char message[255];
} PtkEvent;

/* PTK event API declartions */
void ptk_dispatch(PtkEventType type, PtkEvent event);
int  ptk_add_listener(PtkEventType type, void (*fpointer)(PtkEvent));
void ptk_remove_listener(PtkEventType type, int listener);

#endif
