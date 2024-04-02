#!/bin/bash

if [[ $# == 2 && -f $1 && -f $2 ]]; then
    difference="$(diff "$1" "$2")"
    if [[ "$difference" == "" ]]; then
        exit 0
    else
        exit 1
    fi
else
    exit 2
fi
