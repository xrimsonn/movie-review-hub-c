#!/bin/bash

# Files parameters
OUTPUT_PROGRAM="main.out"
MAIN_SOURCE="src/main.c"
HANDLER_SOURCE="src/handler.c"

# Libraries parameters
COMPILE_OPTIONS="-lmicrohttpd"

# Compilation command
gcc -o $OUTPUT_PROGRAM $MAIN_SOURCE $HANDLER_SOURCE $COMPILE_OPTIONS

if [ $? -eq 0 ]; then
  chmod +x ./$OUTPUT_PROGRAM
  echo "Success, run ./$OUTPUT_PROGRAM."
else
  echo "Compilation error."
fi
