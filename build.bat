@echo off
setlocal EnableDelayedExpansion

rem Create build folder if it doesn't exist
if not exist build mkdir build

rem Get all C files in src folder
set "c_files="
for /r src %%f in (*.c) do (
    set "c_files=!c_files! "%%f""
)

rem Compile all C files
gcc -Wall -Wno-unused-variable -o build\program !c_files!