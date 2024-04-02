#!/bin/bash

cd "$(dirname "$0")" || exit 3

if [[ $# -gt 1 && $# -lt 4 && -f $1 && -f $2 ]]; then
    keys=''
    
    if [[ $# == 3 && -f $3 ]]; then
        keys="$3"
        
    elif [[ $# == 3 ]]; then
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
        if [[ $rc -eq 0 ]]; then
            ./comparator.sh "$2" "out.txt"
            
            rc=$?
            if [[ $rc -eq 0 ]]; then
                exit 0
                
            else
                exit 1
                
            fi
            
        else
            exit 1
            
        fi
        
    else
        exit 2

    fi
    
else
   exit 2

fi
