#!/bin/bash

echo "Select Sandbox mode:"
echo "1 - Sandbox as StaticLib (with Editor) [default]"
echo "2 - Sandbox as ConsoleApp (Editor ignored)"
read -p "Enter your choice (1 or 2): " modeChoice

if [ "$modeChoice" == "2" ]; then
    SANDBOX_MODE="--sandbox-mode=app"
else
    SANDBOX_MODE="--sandbox-mode=lib"
fi

echo "Generating project files with: $SANDBOX_MODE"
vendor/premake/premake5 $SANDBOX_MODE gmake2

read -p "Press Enter to continue..."
