@echo off
echo Select Sandbox mode:
echo 1 - Sandbox as StaticLib (with Editor) [default]
echo 2 - Sandbox as ConsoleApp (no Editor)

set /p modeChoice=Enter your choice (1 or 2): 

if "%modeChoice%"=="2" (
    set SANDBOX_MODE=--sandbox-mode=app
) else (
    set SANDBOX_MODE=--sandbox-mode=lib
)

echo Generating project files with: %SANDBOX_MODE%
vendor\premake\premake5.exe %SANDBOX_MODE% vs2022

PAUSE
