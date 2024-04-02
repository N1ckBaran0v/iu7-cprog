#!/bin/bash

if [[ $# == 2 && -f $1 && -f $2 ]]; then
    OLD_IFS="$IFS"
    IFS="
"
    temp="$(< "$1")"
    first=""
    for line in $temp; do
        if [[ "$first" == "" ]]; then
            first="$(echo "$line" | grep -Poa 'Result: .*$')"
        else
            first="$first $line"
        fi
        # echo "$first"
    done
    temp="$(< "$2")"
    second=""
    for line in $temp; do
        if [[ "$second" == "" ]]; then
            second="$(echo "$line" | grep -Poa 'Result: .*$')"
        else
            second="$second $line"
        fi
        # echo "$second"
    done
    IFS="$OLD_IFS"
    if [[ "$first" == "$second" ]]; then
        exit 0
    else
        exit 1
    fi
else
    exit 2
fi
