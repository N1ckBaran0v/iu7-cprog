#!/bin/bash

list="$(ls *.c)"

for file in $list; do
     gcov "${file}" > "${file}.cov.log"
done
