#!/bin/bash

if ! [ $# -eq 1 ]; then
    echo "no define dir, please run with .sh dirValue"
    exit 1
fi

docker run -it --rm -v $(pwd)/$1:/root/compiler maxxing/compiler-dev bash