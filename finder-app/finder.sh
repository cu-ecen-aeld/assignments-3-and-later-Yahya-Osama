#!/bin/bash

# Check if the number of arguments is not equal to 2
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

# Store the arguments in variables
filesdir="$1"
searchstr="$2"

# Check if filesdir is not a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a directory."
    exit 1
fi

# Find files containing the search string and count them
file_count=$(find "$filesdir" -type f -exec grep -l "$searchstr" {} + | wc -l)

# Find matching lines and count them
match_count=$(find "$filesdir" -type f -exec grep -H "$searchstr" {} + | wc -l)

# Print the results
echo "The number of files are $file_count and the number of matching lines are $match_count"

# Exit with success
exit 0
