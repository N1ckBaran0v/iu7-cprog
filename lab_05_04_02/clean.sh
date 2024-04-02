#!/bin/bash

cd "$(dirname "$0")" || exit 3

rm -f ./*.o ./*.exe ./*.gcov ./*.gcno ./*.gcda \
      ./func_tests/scripts/*.txt ./func_tests/scripts/*.log \
      ./*.log
