#ifndef PTK_TYPES
#define PTK_TYPES

#include <cstdlib>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

/* platform parameter */
typedef struct {
  HINSTANCE hInstance;
  INT iCmdShow;
} PlatformParam;

/* window */
typedef struct {
  HWND instance;
} PtkWindow;

/* menu */
typedef int PtkAccelGroup;
typedef HMENU__ PtkMenuBar;
typedef HMENU__ PtkMenu;
typedef struct {
  LPCWSTR name;
  PtkMenu *submenu;
} PtkMenuItemStruct;
typedef PtkMenuItemStruct PtkMenuItem;
typedef PtkMenuItemStruct PtkMenuSeparator;

typedef HDC__ PtkCanvas;

#endif
