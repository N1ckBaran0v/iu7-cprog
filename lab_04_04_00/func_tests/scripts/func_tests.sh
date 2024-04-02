#!/bin/bash

cd "$(dirname "$0")" || exit 3

rc=0

temp=$(ls ../data)
for file in $(echo "$temp" | grep -Poa "pos_[0-9]*_in\.txt"); do
    input="../data/$file"
    out="../data/pos_$(echo "$file" | grep -Poa "[0-9]*")_out.txt"
    args="../data/pos_$(echo "$file" | grep -Poa "[0-9]*")_args.txt"
    ./pos_case.sh "$input" "$out" "$args"
    ec="$?"
    if [[ $ec -eq 0 ]]; then
        echo -e "\033[0;32mTest with $file passed!\033[0m"
        echo -e "\033[1;33mMemory wasn't checked!\033[0m"
    elif [[ $ec -eq 100 ]]; then
        echo -e "\033[0;32mTest with $file passed!\033[0m"
        echo -e "\033[0;32mMemory passed!"
    else
        rc=$((rc+1))
        if [[ $ec -eq 200 ]]; then
            echo -e "\033[0;31mError while executing pos_case.sh with $file\033[0m"
        fi
        if [[ $((ec%2)) -eq 1 ]]; then
            echo -e "\033[0;31mTest with $file failed! Wrong answer!\033[0m"
        elif [[ $((ec%100)) -ge 10 ]]; then
            echo -e "\033[0;31mTest with $file failed! app.exe terminated!\033[0m"
        else
            echo -e "\033[0;32mTest with $file passed!\033[0m"
        fi
        if [[ $ec -ge 100 && $ec -lt 200 ]]; then
            if [[ $((ec%10)) -ge 2 ]]; then
                echo -e "\033[0;31mMemory failed!\033[0m"
            else
                echo -e "\033[0;32mMemory passed!\033[0m"
            fi
        else
            echo -e "\033[1;33mMemory wasn't checked!\033[0m"
        fi
    fi
done

for file in $(echo "$temp" | grep -Poa "neg_[0-9]*_in\.txt"); do
    input="../data/$file"
    args="../data/neg_$(echo "$file" | grep -Poa "[0-9]*")_args.txt"
    ./neg_case.sh "$input" "$args"
    ec="$?"
    if [[ $ec -eq 0 ]]; then
        echo -e "\033[0;32mTest with $file passed!\033[0m"
        echo -e "\033[1;33mMemory wasn't checked!\033[0m"
    elif [[ $ec -eq 100 ]]; then
        echo -e "\033[0;32mTest with $file passed!\033[0m"
        echo -e "\033[0;32mMemory passed!\033[0m"
    else
        rc=$((rc+1))
        if [[ $ec -eq 200 ]]; then
            echo -e "\033[0;31mError while executing neg_case.sh with $file\033[0m"
        fi
        if [[ $((ec%2)) -eq 1 ]]; then
            echo -e "\033[0;31mTest with $file failed! app.exe don't terminated!\033[0m"
        else
            echo -e "\033[0;32mTest with $file passed!\033[0m"
        fi
        if [[ $ec -ge 100 && $ec -lt 200 ]]; then
            if [[ $((ec%10)) -ge 2 ]]; then
                echo -e "\033[0;31mMemory failed!\033[0m"
            else
                echo -e "\033[0;32mMemory passed!\033[0m"
            fi
        else
            echo -e "\033[1;33mMemory wasn't checked!\033[0m"
        fi
    fi
done

exit $rc
