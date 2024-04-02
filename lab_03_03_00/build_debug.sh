#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -ggdb -O0 --coverage -c main.c

gcc --coverage -o app.exe main.o -lm
