#!/bin/bash

list="$(ls ./*.c)"
rc=0

for file in $list; do
    gcc -std=c99 -Wall -Werror -Wpedantic -Wextra \
        -Wfloat-equal -Wfloat-conversion -Wvla \
        -c "${file}" > "${file}.log" 2>&1
    if [[ "$(< "${file}".log)" != "" ]]; then
        rc=$((rc+1))
    fi
done 

if [[ $rc -eq 0 ]]; then
    list="$(ls ./*.o)"
    obj=""
    
    for file in $list; do
        obj="${obj} ${file}"
    done
    
    command="gcc -o app.exe${obj} -lm"
    eval "${command}" > app.log 2>&1
    if [[ "$(< app.log)" != "" ]]; then
        rc=$((rc+1))
    fi
fi

exit $rc
