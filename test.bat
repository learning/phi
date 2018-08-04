rd /s /q dist
md dist
cl.exe -c src\test.c src\backend\*.c /TP -Fodist\
link.exe dist\*.obj /OUT:dist\test.exe
dist\test.exe C:\\Users\\Learning\\Documents\\Projects\\phi\\test.xml
