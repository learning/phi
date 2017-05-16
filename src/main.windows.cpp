#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "phi/app.h"
using namespace Gdiplus;
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"") 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
  MSG                 msg;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR           gdiplusToken;

  // Initialize GDI+.
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  PlatformParam param = { hInstance, iCmdShow };
  phi_init(param);

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  GdiplusShutdown(gdiplusToken);
  return msg.wParam;
}
