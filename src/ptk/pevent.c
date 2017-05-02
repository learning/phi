#include <stdlib.h>
#include "pevent.h"

/* PTK listener struct */
typedef struct _ptk_listener {
  int id;
  void (*fpointer)(PtkEvent);
  struct _ptk_listener *next;
} PtkListener;

int _pevent_lid = 0;
PtkListener *_pevent_listeners[NUMBER_OF_EVENTS] = { NULL };

void ptk_dispatch(PtkEventType type, PtkEvent event) {
  PtkListener *lp = _pevent_listeners[type];

  // Dispatch to every handler
  while (lp != NULL) {
    (*lp->fpointer)(event);
    lp = lp->next;
  }
}

int ptk_add_listener(PtkEventType type, void (*fpointer)(PtkEvent)) {
  int id = ++_pevent_lid;
  PtkListener *lp = _pevent_listeners[type];
  PtkListener *listener = (PtkListener *) malloc(sizeof(PtkListener));
  listener->id = id;
  listener->fpointer = fpointer;
  listener->next = lp;
  _pevent_listeners[type] = listener;
  return id;
}

void ptk_remove_listener(PtkEventType type, int listener) {
  PtkListener *lp = _pevent_listeners[type];
  while (lp && lp != NULL) {
    if (lp->id == listener) {
      // MUST use last pointer to delete;
    } else {
      lp = lp->next;
    }
  }
}
