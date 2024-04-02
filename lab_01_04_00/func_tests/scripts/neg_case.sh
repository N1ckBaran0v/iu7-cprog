#!/bin/bash

cd "$(dirname "$0")" || exit 3

if [[ $# -gt 0 && $# -lt 3 && -f $1 ]]; then
    keys=''
    
    if [[ $# == 2 && -f $2 ]]; then
        keys=$(cat "$2")
        
    elif [[ $# == 2 ]]; then
        exit 2
        
    fi
    
    if [[ -f ../../app.exe ]]; then
        if [[ "$keys" == "" ]]; then
            if [[ "$USE_VALGRIND" == "" ]]; then
                eval "../../app.exe < $1 > out.txt"
            else
                eval "valgrind --leak-check=full --leak-resolution=high --log-file=memcheck.log ../../app.exe < $1 > out.txt"
            fi
        else
            if [[ "$USE_VALGRIND" == "" ]]; then
                eval "../../app.exe < $1 > out.txt $(< "$keys")"
            else
                eval "valgrind --leak-check=full --leak-resolution=high --log-file=memcheck.log ../../app.exe < $1 > out.txt $(< "$keys")"
            fi
        fi
        
        rc=$?
        if [[ $rc -ne 0 ]]; then
            exit 0

        else
            exit 1
            
        fi
        
    else
        exit 2

    fi
    
else
   exit 2

fi
