#!/bin/bash

cd "$(dirname "$0")"/../../ || exit 3

if [[ $# -ge 1 && $# -le 2 && -f $1 ]]; then
    # cd ../../ || exit 3
    rc=0
    out="./func_tests/scripts/neg_$(echo "$1" | grep -Poa "[0-9]*").txt"
    start="./app.exe"
    valg="./func_tests/scripts/neg_$(echo "$1" | grep -Poa "[0-9]*")_mem.log"
    if [[ -v USE_VALGRIND ]]; then
        start="valgrind --leak-check=full --leak-resolution=high --log-file=$valg $start"
        rc=$((rc+100))
    fi
    if [[ $# -eq 2 && -f $2 ]]; then
        start="$start $(< "$2")"
    fi
    # start="$start"
    # echo "$start"
    eval "$start" < "$1" > "${out}" 2>&1
    ec=$?
    # echo "$ec"
    if [[ $ec -eq 0 ]]; then
        rc=$((rc+1))
    fi
    if [[ -v USE_VALGRIND ]]; then
        last="$(grep -Poa 'ERROR SUMMARY: .' "$valg")"
        if [[ "$last" != "ERROR SUMMARY: 0" ]]; then
            rc=$((rc+2))
        fi
    fi
    cd ./func_tests/scripts/ || exit 3
    exit $rc
else
    exit 200
fi
