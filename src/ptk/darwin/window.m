#include "../window.h"
#include "../pevent.h"

/* Custom controls interfaces */
@interface CustomWindow : NSWindow
@property (strong) id<NSWindowDelegate> customDelegate;
@end

@interface CustomWindowController : NSWindowController <NSWindowDelegate> @end

@interface CustomView : NSView <NSTextInputClient>
@property PtkWindow *pWindow;
@property void (*drawingCallback)(PtkWindow *, PtkCanvas *, int, int);
@property void (*pressCallback)(PtkWindow *, PtkButtonType, unsigned int, int, int);
@property void (*releaseCallback)(PtkWindow *, PtkButtonType, unsigned int, int, int);
@end

/* Custom View declaration */
@implementation CustomView

/* -==== NSTextInputClient ====- */
- (BOOL)acceptsFirstResponder {
  return YES;
}

- (BOOL)becomeFirstResponder {
  return YES;
}

- (BOOL)resignFirstResponder {
  return YES;
}

- (NSArray<NSString *> *) validAttributesForMarkedText {
  // We only allow these attributes to be set on our marked text (plus standard attributes)
  // NSMarkedClauseSegmentAttributeName is important for CJK input, among other uses
  // NSGlyphInfoAttributeName allows alternate forms of characters
  return [NSArray arrayWithObjects:NSMarkedClauseSegmentAttributeName, NSGlyphInfoAttributeName, nil];
}
/*
- (NSAttributedString *)attributedSubstringForProposedRange:(NSRange)range actualRange:(NSRangePointer)actualRange {
  
}*/

- (BOOL)hasMarkedText {
  NSLog(@"hasMarkedText");
  return NO;
}

- (NSRange)markedRange {
  NSLog(@"markedRange");
  return NSMakeRange(0, 0);
}

- (NSRange)selectedRange {
  NSLog(@"selectedRange");
  return NSMakeRange(0, 0);
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point {
  NSLog(@"characterIndexForPoint");
  return 0;
}

- (void)insertText:(id)string replacementRange:(NSRange)replacementRange {
  NSLog(@"insertText: %@", string);
}

- (void)setMarkedText:(id)string selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange {
  NSLog(@"setMarkerText:selectedRange:replacementRange");
}

- (void)unmarkText {
  NSLog(@"unmarkText");
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(NSRangePointer)actualRange {
  NSLog(@"firstRectForCharacterRange:actualRange");
  return NSMakeRect(0, 0, 0, 0);
}

/* -==== NSTextInputClient ====- */

- (BOOL)isFlipped {
    return YES;
}

// Drawing Codes
- (void)drawRect:(NSRect)dirtyRect {
  [super drawRect:dirtyRect];
  if (self.drawingCallback != nil) {
    CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
    CGSize size = self.frame.size;
    (*self.drawingCallback)(nil, context, size.width, size.height);
  }
}


- (void)keyDown:(NSEvent *)theEvent {
  [[self inputContext] handleEvent:theEvent];
}

- (void)mouseDragged:(NSEvent *)theEvent {
  [[self inputContext] handleEvent:theEvent];
}

// Mouse handling
// 0: left
// 1: right
// 2: middle
// 3: back
// 4: forward
- (void)mouseDown:(NSEvent *)event {
  [[self inputContext] handleEvent:event];
  if (self.pressCallback != nil) {
    CGPoint point = [event locationInWindow];
    point = [self convertPoint:point fromView:nil];
    (*self.pressCallback)(self.pWindow, PTK_BUTTON_LEFT, 0, point.x, point.y);
  }
}

- (void)rightMouseDown:(NSEvent *)event {
  if (self.pressCallback != nil) {
    CGPoint point = [event locationInWindow];
    point = [self convertPoint:point fromView:nil];
    (*self.pressCallback)(self.pWindow, PTK_BUTTON_RIGHT, 0, point.x, point.y);
  }
}

- (void)otherMouseDown:(NSEvent *)event {
  if (self.pressCallback != nil) {
    CGPoint point = [event locationInWindow];
    point = [self convertPoint:point fromView:nil];
    PtkButtonType button;
    if (event.buttonNumber == 2) {
      button = PTK_BUTTON_MIDDLE;
    } else {
      button = PTK_BUTTON_UNKNOWN;
    }
    (*self.pressCallback)(self.pWindow, button, 0, point.x, point.y);
  }
}

- (void)mouseUp:(NSEvent *)event {
  [[self inputContext] handleEvent:event];
  if (self.releaseCallback != nil) {
    CGPoint point = [event locationInWindow];
    point = [self convertPoint:point fromView:nil];
    (*self.releaseCallback)(self.pWindow, PTK_BUTTON_LEFT, 0, point.x, point.y);
  }
}

- (void)rightMouseUp:(NSEvent *)event {
  if (self.releaseCallback != nil) {
    CGPoint point = [event locationInWindow];
    point = [self convertPoint:point fromView:nil];
    (*self.releaseCallback)(self.pWindow, PTK_BUTTON_RIGHT, 0, point.x, point.y);
  }
}

- (void)otherMouseUp:(NSEvent *)event {
  if (self.releaseCallback != nil) {
    CGPoint point = [event locationInWindow];
    point = [self convertPoint:point fromView:nil];
    PtkButtonType button;
    if (event.buttonNumber == 2) {
      button = PTK_BUTTON_MIDDLE;
    } else {
      button = PTK_BUTTON_UNKNOWN;
    }
    (*self.releaseCallback)(self.pWindow, button, 0, point.x, point.y);
  }
}

- (NSMenu *)menuForEvent:(NSEvent *)event {
  NSLog(@"menuforevent");
  return nil;
}

@end

/* Custom Window & Controller declaration */
@implementation CustomWindow
@end

@implementation CustomWindowController

- (void)windowWillClose:(NSNotification *)notification {
  PtkEvent evt = { "window_close" };
  ptk_dispatch(PTK_WINDOW_CLOSE, evt);
  NSLog(@"window will close.");
}

@end

PtkWindow *ptk_window_new(int width, int height, PtkMenuBar *menuBar, PlatformParam param) {

  NSUInteger windowStyle = NSTitledWindowMask |
                           NSClosableWindowMask |
                           NSResizableWindowMask;
  
  // Window bounds (x, y, width, height).
  NSRect windowRect = NSMakeRect(0, 0, width, height);
  CustomWindow * instance = [[CustomWindow alloc] initWithContentRect:windowRect
                                                  styleMask:windowStyle
                                                    backing:NSBackingStoreBuffered
                                                      defer:NO];

  // [instance cascadeTopLeftFromPoint:NSMakePoint(20,20)];
  [instance makeKeyAndOrderFront:nil];
  
  // Window controller:
  CustomWindowController *winController = [[CustomWindowController alloc] initWithWindow:instance];
  [instance setDelegate:winController];
  [instance setCustomDelegate:winController];
  
  // Add custom view
  CustomView * view = [[CustomView alloc] initWithFrame:windowRect];
  
  [instance setContentView:view];

  // Show instance and run event loop.
  [instance orderFrontRegardless];

  if (menuBar != nil) {
    [NSApp setMainMenu:menuBar];
  }

  PtkWindow *window = malloc(sizeof(PtkWindow));
  window->instance = instance;
  window->controller = winController;
  window->view = view;
  [view setPWindow:window];
  return window;
}

void ptk_window_set_title(PtkWindow *window, const char title[]) {
  NSString *_title = [NSString stringWithFormat:@"%s", title];
  [window->instance setTitle:_title];
}

void ptk_window_set_drawing_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkCanvas *, int, int)) {
  [(CustomView *)window->view setDrawingCallback:fpointer];
}

void ptk_window_set_button_press_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkButtonType, unsigned int, int, int)) {
  [(CustomView *)window->view setPressCallback:fpointer];
}

void ptk_window_set_button_release_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, PtkButtonType, unsigned int, int, int)) {
  [(CustomView *)window->view setReleaseCallback:fpointer];
}

void ptk_window_set_input_callback(PtkWindow *window, void (*fpointer)(PtkWindow *, const char *)) {
  
}
