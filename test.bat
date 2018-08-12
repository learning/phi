rd /s /q dist
md dist
cl.exe -c src\test.windows.cpp src\backend\*.c /TP -Fodist\
link.exe dist\*.obj /OUT:dist\test.exe
dist\test.exe test.xml
