#include "../window.h"
#include "../pevent.h"

/* Custom controls interfaces */
@interface CustomWindow : NSWindow
@property (strong) id<NSWindowDelegate> customDelegate;
@end

@interface CustomWindowController : NSWindowController <NSWindowDelegate> @end

@interface CustomView : NSView <NSTextInputClient>
  @property PtkWindow *ptkWindow;
  @property WindowDrawCallback windowDrawCallback;
  @property MousePressCallback mousePressCallback;
  @property MouseReleaseCallback mouseReleaseCallback;
  @property KeyboardInputCallback keyboardInputCallback;
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
    if (self.windowDrawCallback != nil) {
      CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
      CGSize size = self.frame.size;
      (*self.windowDrawCallback)(nil, context, size.width, size.height);
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
    if (self.mousePressCallback != nil) {
      CGPoint point = [event locationInWindow];
      point = [self convertPoint:point fromView:nil];
      (*self.mousePressCallback)(self.ptkWindow, PTK_MOUSE_LEFT, 0, point.x, point.y);
    }
  }

  - (void)rightMouseDown:(NSEvent *)event {
    if (self.mousePressCallback != nil) {
      CGPoint point = [event locationInWindow];
      point = [self convertPoint:point fromView:nil];
      (*self.mousePressCallback)(self.ptkWindow, PTK_MOUSE_RIGHT, 0, point.x, point.y);
    }
  }

  - (void)otherMouseDown:(NSEvent *)event {
    if (self.mousePressCallback != nil) {
      CGPoint point = [event locationInWindow];
      point = [self convertPoint:point fromView:nil];
      PtkMouseType button;
      if (event.buttonNumber == 2) {
        button = PTK_MOUSE_MIDDLE;
      } else {
        button = PTK_MOUSE_UNKNOWN;
      }
      (*self.mousePressCallback)(self.ptkWindow, button, 0, point.x, point.y);
    }
  }

  - (void)mouseUp:(NSEvent *)event {
    [[self inputContext] handleEvent:event];
    if (self.mouseReleaseCallback != nil) {
      CGPoint point = [event locationInWindow];
      point = [self convertPoint:point fromView:nil];
      (*self.mouseReleaseCallback)(self.ptkWindow, PTK_MOUSE_LEFT, 0, point.x, point.y);
    }
  }

  - (void)rightMouseUp:(NSEvent *)event {
    if (self.mouseReleaseCallback != nil) {
      CGPoint point = [event locationInWindow];
      point = [self convertPoint:point fromView:nil];
      (*self.mouseReleaseCallback)(self.ptkWindow, PTK_MOUSE_RIGHT, 0, point.x, point.y);
    }
  }

  - (void)otherMouseUp:(NSEvent *)event {
    if (self.mouseReleaseCallback != nil) {
      CGPoint point = [event locationInWindow];
      point = [self convertPoint:point fromView:nil];
      PtkMouseType button;
      if (event.buttonNumber == 2) {
        button = PTK_MOUSE_MIDDLE;
      } else {
        button = PTK_MOUSE_UNKNOWN;
      }
      (*self.mouseReleaseCallback)(self.ptkWindow, button, 0, point.x, point.y);
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
  PtkWindow *ptkWindow = [(CustomView *) self.window.contentView ptkWindow];
  PtkEvent evt = { "window_close", ptkWindow };
  ptk_dispatch(PTK_WINDOW_CLOSE, evt);
  // [self.window dealloc];
  // [self.window.contentView dealloc];
  // [self dealloc];
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
  [view setPtkWindow:window];
  
  return window;
}

void ptk_window_set_title(PtkWindow *window, const char title[]) {
  NSString *_title = [NSString stringWithFormat:@"%s", title];
  [window->instance setTitle:_title];
}

void ptk_window_add_accel_group(PtkWindow *window, PtkAccelGroup *accel_group) {
  NSLog(@"ptk_window_add_accel_group");
}

void ptk_window_set_window_draw_callback(PtkWindow *window, WindowDrawCallback callback) {
  [(CustomView *)window->view setWindowDrawCallback:callback];
}

void ptk_window_set_mouse_press_callback(PtkWindow *window, MousePressCallback callback) {
  [(CustomView *)window->view setMousePressCallback:callback];
}

void ptk_window_set_mouse_release_callback(PtkWindow *window, MouseReleaseCallback callback) {
  [(CustomView *)window->view setMouseReleaseCallback:callback];
}

void ptk_window_set_keyboard_input_callback(PtkWindow *window, KeyboardInputCallback callback) {
  [(CustomView *)window->view setKeyboardInputCallback:callback];
}
