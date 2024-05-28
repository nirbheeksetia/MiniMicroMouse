#!/bin/bash
cd /mnt/c/Users/79522/MiniMicroMouse
g++ -g alg.cpp API.cpp -o alg
if [ $? -eq 0 ]; then
    ./alg
else
    echo "Compilation failed"
fi
