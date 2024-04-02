#!/bin/bash

if [[ $# == 2 && -f $1 && -f $2 ]]; then
    first=$(grep -Poa 'Result: .*$' "$1")
    # echo $first
    second=$(grep -Poa 'Result: .*$' "$2") 
    # echo $second
    if [[ "$first" == "$second" ]]; then
        exit 0
    else
        exit 1
    fi
else
    exit 2
fi
