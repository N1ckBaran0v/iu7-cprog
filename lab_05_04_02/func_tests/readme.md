# Tests for task 4

## Input data: 

In case append:

String name

String producer

uint32_t cost

uint32_t count

## Output data:

In case output:

String name

String producer

uint32_t cost

uint32_t count

## Command line args: 

sb fin fout - sort file

fb filename pattern - print which match

ab filename - add to file

## Positive tests:

- 01 - 1 product in file: print;
- 02 - Sort previous;
- 03 - Print previous;
- 04 - Append larger to previous;
- 05 - Print previous;
- 06 - Append smaller to previous;
- 07 - Print previous;
- 08 - Already sorted file: print;
- 09 - Sort previous;
- 10 - Print previous;
- 11 - Append largest to previous;
- 12 - Print previous;
- 13 - Reversed file: print;
- 14 - Sort previous;
- 15 - Print previous;
- 16 - Append smallest to previous;
- 17 - Print previous;
- 18 - Unsorted file: print;
- 19 - Sort previous;
- 20 - Print previous;
- 21 - Append largest to previous;
- 22 - Print previous;
- 23 - Only 1 match while print;
- 24 - All matched while print;
- 25 - Some matched while print.

## Negative tests:

- 01 - No args;
- 02 - Incorrect args;
- 03 - Args for text (while print);
- 04 - Args for text (while sort);
- 05 - Args for text (while append);
- 06 - File empty (while print);
- 07 - File empty (while sort);
- 08 - File empty (while append);
- 09 - File unsorted while append;
- 10 - No match while output;
- 11 - Error while read to append.

