#!/bin/bash

#Check if no of arguments is less than 2
if [ $# -ne 2 ]
then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

#Store Arguments into variables
writefile="$1"
writestr="$2"

# Create the directory path if it doesn't exist
mkdir -p "$(dirname "$writefile")"

echo "$writestr" > "$writefile"

if [ $? -ne 0 ]
then
    echo "Error: Could not create or write to file $writefile "
    exit 1
fi

echo "File $writefile created with content: $writestr"
exit 0