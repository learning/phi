#ifndef __PTK_TYPES__
#define __PTK_TYPES__

#import <Cocoa/Cocoa.h>
#include <CoreGraphics/CGContext.h>

/* platform parameter */
typedef int PlatformParam;

/* menu */
typedef NSMenu PtkMenuBar;
typedef NSMenu PtkMenu;
typedef NSMenuItem PtkMenuItem;
typedef NSMenuItem PtkMenuSeparator;

/* window */
typedef struct {
  __unsafe_unretained NSWindow *instance;
  __unsafe_unretained NSWindowController *controller;
  __unsafe_unretained NSView *view;
} PtkWindow;

typedef struct CGContext PtkCanvas;

// typedef int PtkTextLayout;
#endif
