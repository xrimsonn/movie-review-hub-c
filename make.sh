#!/bin/bash

# Files parameters
OUTPUT_PROGRAM="main.out"
MAIN_SOURCE="src/main.c"
HANDLER_SOURCE="src/handler.c"

# Libraries parameters
COMPILE_OPTIONS="-I/usr/include/libbson-1.0 -I/usr/include/libmongoc-1.0 -L/usr/lib64 -lbson-1.0 -lmongoc-1.0 -lcjson -lmicrohttpd -pthread -lhttp_parser"

# Compilation command
gcc -o $OUTPUT_PROGRAM $MAIN_SOURCE $HANDLER_SOURCE $COMPILE_OPTIONS

if [ $? -eq 0 ]; then
  chmod +x ./$OUTPUT_PROGRAM
  echo "Success, run ./$OUTPUT_PROGRAM."
else
  echo "Compilation error."
fi
