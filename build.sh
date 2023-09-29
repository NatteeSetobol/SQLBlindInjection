#!/bin/bash

MAIN_FILE="../main.cpp"
COMPILER="g++"
MACROS="-DLINUX=1 -DDEBUGGING=1"
CPP="../../lpop/nix_threading.cpp ../../lpop/queue.cpp ../../lpop/strings.cpp ../../lpop/array.cpp ../../lpop/token.cpp ../../lpop/required/memory.cpp ../../lpop/required/nix.cpp ../../lpop/bucket.cpp ../../lpop/cl_options.cpp ../../lpop/socket.cpp  ../../lpop/nix_socket.cpp ../../lpop/base64.cpp ../../lpop/curled.cpp ../../lpop/htmlparser.cpp" 
FLAGS="-w -g  -lcurl -fsanitize=address" # -DARAM -fsanitize=address
OUTPUT="SQLbruteForce"

if [ "$1" = "TEST" ]
then
	MACROS+=" -DTEST"
fi

if [ -d "build" ]
then
	rm -rf build
fi

mkdir build
cd build
$COMPILER $MACROS $MAIN_FILE $CPP $FLAGS -o $OUTPUT
cd ..
