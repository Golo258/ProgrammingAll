#!/bin/bash

#aray operation: sorting 
types=(a c b f 3 5)
sorted_types=($(for type in "${types[@]}"; do echo $type; done | sort))
echo "Posortowane owoce: ${sorted_types[@]}"

#filtering by letter contains

fruits=("apple" "banana" "cherry")
for fruit in "${fruits[@]}"; do
    if [[ $fruit == b* ]]; then
        printf "Fruit %s starts with b\n" "${fruit}"
    else
        printf "Fruit %s starts with %s\n" "${fruit}" "${fruit:0:1}"
    fi
done



# redirecting intpu to file 
testing_file=output.txt
simple_text="simple text" 
echo "${simple_text}" > $testing_file;
if [ -e $testing_file ] && [ -s $testing_file ]; then
    echo "Second ____ text" >> $testing_file
    cat $testing_file
    # command 2> /dev/null # redirect error 
else
    echo "Not exist"
fi
rm $testing_file
# handling erros
: '
    Each commands in bash is returning output code 
        $? - variable to check the code
        0 code is sucess
'
#1 way
ls /not-known-directory
if [ $? -ne 0 ]; then
    echo "Listing ends with errors"
fi
#2 way
output=$(ls /notexistingdirectory 2>&1)
exit_status=$?

if [ $exit_status -ne 0 ]; then
    echo "Error: $output"
else
    echo "Its not error: $output"
fi

#functions
: '
    arguments as positional argument $1 $2 $3 ... 
    $@- all @! - args count
    $0 - name of current script
    $$ - PID (process id) of script
    $? - exit code of last command 
'

readonly const_var="Const flag"
function simple() {
    echo "Its $1 example of $2"
    for argument in "$@"; do
        echo "${argument}"
    done
    
}
simple first function other $const_var

#default variables $1:-"value"
introduction() {
    local name=${1:-"Not Known"}
    local place=${2:-"Earth"}
    echo "Welcome $name, on the $place"
}
introduction
introduction Marcin  Mars

#creating archives
: '
    tar - tape archive 
        c - create
        x - extract 
        t - list - show archive
        r - append - new file to archieve
        --delete - remove file from archive
        v - verbose - info about process
        f - file -  specify archive name
        -cvf  archiwum.tar file1 file2 katalog//
'
manage_archive() {
    case $1 in
        create) 
            echo "Creating case"
            tar -cvf $2 $3;;
        view) 
            echo "VIewing case"
            tar -tvf $2;;
        update)
            echo "Updating archive"
            tar -rvf $2 $3;;

        remove) 
            echo "Removing file $"
            tar --delete -f $2 $3;;
        extract) echo 
            "Extracting case"
            tar -xvf $2 -C $3;; # -C presice where to unpack
        *) echo "Other sign ";;
    esac
    # 
}
manage_archive create Static/Archive/files.tar Static/ArcFiles/\*
manage_archive view Static/Archive/files.tar
manage_archive update Static/Archive/files.tar additional.txt
manage_archive remove Static/Archive/files.tar to_remove.txt
manage_archive extract Static/Archive/files.tar  Static/ArcExtract/
echo "Removal of Arc folder"
rm -rf Arc/a


# tee  - saving output to file
tree | tee folders_list.txt
# creating logs file 
process_with_many_output | tee -a process_logs.txt
: '
    tail - show last part of file (default 10 lines)
        -n - line number 
        -f - follow changes


'   
# sed 
sed 's/old_version/new_version/g' file.txt
: '
    sed - changing text  | removing lines | showing lines 
    s - start of seding 

'
# awk
