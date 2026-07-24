@echo off
REM Build script for debug_demo.exe
REM Requires Visual Studio build environment (cl.exe)

echo Building debug_demo.exe...
echo.

cl /Fe:debug_demo.exe ^
   debug_demo.c ^
   ../../src/debug.c ^
   user32.lib kernel32.lib gdi32.lib ^
   /link /SUBSYSTEM:WINDOWS

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Running debug_demo.exe...
    echo.
    debug_demo.exe
) else (
    echo.
    echo Build failed. Make sure you have Visual Studio build tools installed.
    echo Try: "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
    echo.
)

pause
