#!/bin/bash

cd "$(dirname "$0")" || exit 3

rm -f ./*.o ./*.exe ./*.gcov ./*.gcno ./*.txt ./*.gcda ./func_tests/scripts/*.txt ./func_tests/scripts/*.log
