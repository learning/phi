#import <Cocoa/Cocoa.h>
#include "phi/app.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation AppDelegate

- (void)windowCloseHandler {
  NSLog(@"windowCloseHandler");
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  [[NSNotificationCenter defaultCenter]
    addObserver:[NSObject new]
    selector:@selector(windowCloseHandler)
    name:NSWindowWillCloseNotification
    object:nil];
  NSLog(@"applicationDidFinishLaunching.");
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
  NSLog(@"applicationWillTerminate.");
}

@end


int main (int argc, const char * argv[])
{
  // Create a shared app instance.
  // This will initialize the global variable
  // 'NSApp' with the application instance.
  [NSApplication sharedApplication];

  // Set app to front
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
  [NSApp activateIgnoringOtherApps:YES];

  // Remove default menu items
  [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"NSDisabledDictationMenuItem"];
  [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"NSDisabledCharacterPaletteMenuItem"];

  // Entry point
  phi_init(0);

  AppDelegate *appDelegate = [[AppDelegate alloc] init];
  [NSApp setDelegate:appDelegate];

  [NSApp run];

  return 0;
}
