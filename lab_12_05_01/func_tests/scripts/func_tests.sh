#!/bin/bash

cd "$(dirname "$0")" || exit 3

rc=0

temp=$(ls ../data)
for file in $(echo "$temp" | grep -Poa "pos_[0-9]*_in\.txt"); do
    input="./func_tests/data/$file"
    out="./func_tests/data/pos_$(echo "$file" | grep -Poa "[0-9]*")_out.txt"
    args="./func_tests/data/pos_$(echo "$file" | grep -Poa "[0-9]*")_args.txt"
    ./pos_case.sh "$input" "$out" "$args"
    ec="$?"
    if [[ $ec -eq 0 ]]; then
        echo -e "POS CASE ${file}: \033[0;32mOK!\033[0m"
        echo -e "POS CASE ${file}: \033[1;33mMEMORY UNTESTED!\033[0m"
    elif [[ $ec -eq 100 ]]; then
        echo -e "POS CASE ${file}: \033[0;32mOK!\033[0m"
        echo -e "POS CASE ${file}: \033[0;32mMEMORY OK!\033[0m"
    else
        rc=$((rc+1))
        if [[ $ec -eq 200 ]]; then
            echo -e "\033[0;31mERROR\033[0m while executing pos_case.sh with $file"
        fi
        if [[ $((ec%2)) -eq 1 ]]; then
            echo -e "POS CASE ${file}: \033[0;31mERROR!\033[0m\nWrong answer!"
        elif [[ $((ec%100)) -ge 10 ]]; then
            echo -e "POS CASE ${file}: \033[0;31mERROR!\033[0m\napp.exe terminated!"
        else
            echo -e "POS CASE ${file}: \033[0;32mOK!\033[0m"
        fi
        if [[ $ec -ge 100 && $ec -lt 200 ]]; then
            if [[ $((ec%10)) -ge 2 ]]; then
                echo -e "POS CASE ${file}: \033[0;31mMEMORY ERROR!\033[0m"
            else
                echo -e "POS CASE ${file}: \033[0;32mMEMORY OK!\033[0m"
            fi
        else
            echo -e "POS CASE ${file}: \033[1;33mMEMORY UNTESTED!\033[0m"
        fi
    fi
done

for file in $(echo "$temp" | grep -Poa "neg_[0-9]*_in\.txt"); do
    input="./func_tests/data/$file"
    args="./func_tests/data/neg_$(echo "$file" | grep -Poa "[0-9]*")_args.txt"
    ./neg_case.sh "$input" "$args"
    ec="$?"
    if [[ $ec -eq 0 ]]; then
        echo -e "NEG CASE ${file}: \033[0;32mOK!\033[0m"
        echo -e "NEG CASE ${file}: \033[1;33mMEMORY UNTESTED!\033[0m"
    elif [[ $ec -eq 100 ]]; then
        echo -e "NEG CASE ${file}: \033[0;32mOK!\033[0m"
        echo -e "NEG CASE ${file}: \033[0;32mMEMORY OK!\033[0m"
    else
        rc=$((rc+1))
        if [[ $ec -eq 200 ]]; then
            echo -e "\033[0;31mERROR\033[0m while executing neg_case.sh with $file"
        fi
        if [[ $((ec%2)) -eq 1 ]]; then
            echo -e "NEG CASE ${file}: \033[0;31mERROR!\033[0m\napp.exe don't terminated!"
        else
            echo -e "NEG CASE ${file}: \033[0;32mOK!\033[0m"
        fi
        if [[ $ec -ge 100 && $ec -lt 200 ]]; then
            if [[ $((ec%10)) -ge 2 ]]; then
                echo -e "NEG CASE ${file}: \033[0;31mMEMORY ERROR!\033[0m"
            else
                echo -e "NEG CASE ${file}: \033[0;32mMEMORY OK!\033[0m"
            fi
        else
            echo -e "NEG CASE ${file}: \033[1;33mMEMORY UNTESTED!\033[0m"
        fi
    fi
done

exit $rc
