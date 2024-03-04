#!/bin/bash

source init.sh

# Create build folder if it doesn't exist
mkdir -p build/

# Get all C files in src folder
c_files=$(find src/ -name '*.c')

# Compile all C files
gcc -Wall -o build/program $c_files