#!/bin/bash

# files operations
: '
    && its like and operator which connect comparisons
    and 
        mkdir <name> && cd new_dir 
            - it run only if there are not error after first command

    | - passing output from one to another command
    ls -l | grep "file_name"

    -e - file exists

'

files=$(ls)
for item in "${files[@]}"; do
    echo "File element : ${item}"
done


file_path="Static/xd.txt"
if [ -e $file_path ] && [ -f $file_path ] && [ -s $file_path ]; then
    echo "FIle exists and is not empty"
    cat $file_path
else
    potential_files=()
    mapfile -t potential_files < <(find . -maxdepth 2 -type f -name "*.txt")
    if [ -z "${potential_files}" ]; then
        echo "Creating and init new file"
        touch $file_path
        echo "Random test from script" > $file_path
    else
        for item in "${potential_files[@]}"; do
            cat $item
        done
    fi
fi