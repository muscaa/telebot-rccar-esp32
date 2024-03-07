@echo off
cls
setlocal EnableDelayedExpansion

rem Create build folder if it doesn't exist
if not exist build mkdir build

rem Get all C files in src folder
set "C_FILES="
for /r src %%f in (*.c) do (
    set "C_FILES=!C_FILES! "%%f""
)

rem Compile all C files
gcc -Wall -o build\program %C_FILES%

rem Run program if compilation was successful
if %errorlevel% equ 0 (
    cd build
    program %*
    set exit_code=!errorlevel!
    
    echo.
    echo.
    echo.
    echo Program exited with code !exit_code!.
    echo.
)
