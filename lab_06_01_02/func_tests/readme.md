# Tests for lab 6 task 1

# Input data: 

# Output data: name, weight and size of object (multiple objjects possible)

# Command line args: filename [prefix (or ALL to output all)]

# Positive tests:

- 01 - 1 object (only filename in args)
- 02 - 3 object (only filename in args)
- 03 - 15 objects (only filename in args)
- 04 - 1 object (ALL)
- 05 - 3 object (ALL)
- 06 - 15 objects (ALL)
- 07 - 1 object (prefix)
- 08 - 3 object (prefix (ex. 1))
- 09 - 3 object (prefix (ex. 2))
- 10 - 15 objects (prefix (ex. 1))
- 11 - 15 objects (prefix (ex. 2))
- 12 - 15 objects (prefix (ex. 3))
- 13 - 1 object (not prefix)
- 14 - 3 object (not prefix)
- 15 - 15 objects (not prefix)
- 16 - already sorted
- 17 - reversed
- 18 - similar values

# Negative tests:

- 01 - no args
- 02 - too much args
- 03 - file not found
- 04 - empty file
- 05 - too long name
- 06 - incorrect number
- 07 - too much objects
