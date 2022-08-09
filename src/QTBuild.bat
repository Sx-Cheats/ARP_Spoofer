@echo off
mkdir release
cd release


C:\Qt\6.3.1\mingw_64\bin\moc.exe ../../headers/window.h -o ../../headers/window.moc
C:\Qt\Tools\mingw1120_64\bin\g++.exe -fpermissive -Wl,-subsystem,windows -mconsole -masm=intel -mthreads -o ARPSpoofer.exe ../main.cpp  -std=c++17 -IC:\Qt\6.3.1\mingw_64\include -LC:\Qt\6.3.1\mingw_64\lib C:\Qt\6.3.1\mingw_64\lib\libQt6Core.a C:\Qt\6.3.1\mingw_64\lib\libQt6Widgets.a C:\Qt\6.3.1\mingw_64\lib\libQt6Gui.a -lmingw32 C:\Qt\6.3.1\mingw_64\lib\libQt6EntryPoint.a -lshell32 -lws2_32 -lpsapi  -liphlpapi -L..\..\Lib\x64 -lwpcap


C:\Qt\6.3.1\mingw_64\bin\windeployqt.exe ./ARPSpoofer.exe
xcopy /s C:\Qt\6.3.1\mingw_64\bin\libstdc++-6.dll . /Y

xcopy /s ..\..\img\da.png . /Y
xcopy /s ..\..\img\Victim.png . /Y
xcopy /s ..\..\img\Attacker.png . /Y
xcopy /s ..\..\img\box.png . /Y

