#!/bin/bash

# Find all cpp files recursively
SOURCES=$(find . -name "*.cpp")

clang++ -std=c++17 -Wall -Wextra -O2 $SOURCES -o adventure

echo "Build complete. Run ./adventure to start."
