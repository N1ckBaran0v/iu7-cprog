#!/bin/bash

cd "$(dirname "$0")" || exit 3

rc=0

temp=$(ls ../data)
for file in $(echo "$temp" | grep -Poa "pos_[0-9]*_in\.txt"); do
    input="../data/$file"
    out="../data/pos_$(echo "$file" | grep -Poa "[0-9]*")_out.txt"
    ./pos_case.sh "$input" "$out"
    ec="$?"
    if [[ $ec != 0 ]]; then
        echo "Test with $file failed!"
        rc=$((rc+1))
    else
        echo "Test with $file passed!"
    fi
done

temp=$(ls ../data)
for file in $(echo "$temp" | grep -Poa "neg_[0-9]*_in\.txt"); do
    input="../data/$file"
    ./neg_case.sh "$input"
    ec=$?
    if [[ $ec != 0 ]]; then
        echo "Test with $file failed!"
        rc=$((rc+1))
    else
        echo "Test with $file passed!"
    fi
done

exit $rc
