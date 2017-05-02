#ifndef __PTK_EVENT__
#define __PTK_EVENT__

/* PTK event type enum */
typedef enum {
  PTK_WINDOW_CLOSE,
  PTK_MENU_ACTIVATE,

  // Count event type number
  NUMBER_OF_EVENTS
} PtkEventType;

/* PTK event struct */
typedef struct {
  char message[255];
} PtkEvent;

/* PTK event API declartions */
void ptk_dispatch(PtkEventType type, PtkEvent event);
int  ptk_add_listener(PtkEventType type, void (*fpointer)(PtkEvent));
void ptk_remove_listener(PtkEventType type, int listener);

#endif
