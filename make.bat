rd /s /q dist
md dist
md dist\ptk
md dist\phi
rd /s /q src\ptk\target
md src\ptk\target
copy src\ptk\win32\*.* src\ptk\target\*.*
cl.exe -c src\ptk\*.c src\ptk\target\*.c /TP -Fodist\ptk\
cl.exe -c src\main.windows.cpp src\phi\*.c /TP -Fodist\phi\
link.exe dist\ptk\*.obj dist\phi\*.obj /OUT:dist\phi.exe
rd /s /q dist\ptk
rd /s /q dist\phi
dist\phi.exe
