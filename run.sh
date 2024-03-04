#!/bin/bash

source init.sh

if [ -f ./build/program ]; then
    ./build/program $@
    exit=$?

    echo
    echo
    echo
    echo "Program exited with code $exit."
    echo
fi