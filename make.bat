rd /s /q dist
md dist
md dist\ptk
rd /s /q src\ptk\target
md src\ptk\target
copy src\ptk\win32\*.* src\ptk\target\*.*
cl.exe src\main.windows.cpp src\ptk\*.c src\ptk\target\*.c src\phi\*.c /TP -Fedist\phi.exe
dist\phi.exe
