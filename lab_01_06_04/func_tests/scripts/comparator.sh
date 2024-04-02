#!/bin/bash

cd "$(dirname "$0")" || exit 3

if [[ $# == 2 && -f $1 && -f $2 ]]; then
    first=$(grep -Poa '[+-]?[0-9]+(\.[0-9]+|)' "$1")
    # echo $first
    second=$(grep -Poa '[+-]?[0-9]+(\.[0-9]+|)' "$2") 
    # echo $second
    if [[ "$first" == "$second" ]]; then
        exit 0
    else
        exit 1
    fi
else
    exit 2
fi
