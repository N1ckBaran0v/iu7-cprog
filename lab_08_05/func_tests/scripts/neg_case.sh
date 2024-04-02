#!/bin/bash

cd "$(dirname "$0")" || exit 3

if [[ $# -ge 1 && $# -le 2 && -f $1 ]]; then
    rc=0
    out="neg_$(echo "$1" | grep -Poa "[0-9]*").txt"
    start="../../app.exe < $1 > ${out} 2>&1"
    valg="neg_$(echo "$1" | grep -Poa "[0-9]*")_mem.log"
    if [[ -v USE_VALGRIND ]]; then
        start="valgrind --leak-check=full --leak-resolution=high --log-file=$valg $start"
        rc=$((rc+100))
    fi
    if [[ $# -eq 2 && -f $2 ]]; then
        start="$start $(< "$2")"
    fi
    eval "$start"
    ec=$?
    if [[ $ec -eq 0 ]]; then
        rc=$((rc+1))
    fi
    if [[ -v USE_VALGRIND ]]; then
        last="$(grep -Poa 'ERROR SUMMARY: .' "$valg")"
        if [[ "$last" != "ERROR SUMMARY: 0" ]]; then
            rc=$((rc+2))
        fi
    fi
    exit $rc
else
    exit 200
fi
