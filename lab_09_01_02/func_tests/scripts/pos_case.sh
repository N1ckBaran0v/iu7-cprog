#!/bin/bash

cd "$(dirname "$0")"/../../ || exit 3

if [[ $# -ge 2 && $# -le 3 && -f $1 && -f $2 ]]; then
    # cd ../../ || exit 3
    rc=0
    out="./func_tests/scripts/pos_$(echo "$1" | grep -Poa "[0-9]*").txt"
    start="./app.exe"
    valg="./func_tests/scripts/pos_$(echo "$1" | grep -Poa "[0-9]*")_mem.log"
    if [[ -v USE_VALGRIND ]]; then
        start="valgrind --leak-check=full --leak-resolution=high --log-file=$valg $start"
        rc=$((rc+100))
    fi
    if [[ $# -eq 3 && -f $3 ]]; then
        start="$start $(< "$3")"
    fi
    # start="$start"
    # echo "$start"
    eval "$start" < "$1" > "${out}" 2>&1
    ec=$?
    # echo "$ec"
    if [[ $ec -eq 0 ]]; then
        ./func_tests/scripts/comparator.sh "$2" "${out}"
        ec=$?
        if [[ $ec -ne 0 ]]; then
            rc=$((rc+1))
        fi
    else
        rc=$((rc+10))
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
