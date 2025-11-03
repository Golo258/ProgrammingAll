#!/bin/bash
# Variable declaration
SIMPLE_VAR="SIemano kolano"
echo "$SIMPLE_VAR"

# For loop wih if statement
for((i=0;i<=5;i++)); do

    if [ ${i} -gt 3 ]; then
        echo "Index is greather then 3: ${i}"
    else 
        echo "Number is lower then 3: ${i}"
    fi
done

#while loop
count=1
while [ $count -le 5 ]; do
    ((count++))
    echo "${count}"
    
done

# until loop
until [ $count -gt 10 ]; do
    ((count++))
done
echo "Last version of count: ${count}"

#functions
simple_func() {
    echo "Hello ${1}"
}
simple_func "Allice"


#input
# echo "Enter name";
# read name
# printf "Helo chico %s\n"  $name

#arras
fruits=("apple" "banana" "cherry")
echo "Array first element: ${fruits[1]}"
echo "Whole array:${fruits[@]}"
echo "Array indexes: ${!fruits[@]}"
#adding elem
fruits+=('orange')
#removal elem
# unset fruits[1]

for index in "${!fruits[@]}"; do
    echo "Fruit on ${index} is: ${fruits[${index}]}"
done

#strings 

content="One word, two words"
echo "${content:0:8}" # sl,ices

IFS=' ' read -r -a content_array <<< "$content"
echo "Converted string to array: ${content_array[@]}"



# Parrarels
: '
    [[ ... ]] - tests and comparisons 
        more advanced then [], regex 
    [ ... ] - less used, comparison with conditions

    Numbers comparisons
        -eq: Równe
        -ne: Różne
        -lt: Mniejsze niż
        -le: Mniejsze lub równe
        -gt: Większe niż
        -ge: Większe lub równe
        Used with single []

    "" - variables are recognized
    '' - varibales are not recognized

'-z STRING
              the length of STR
numb=5
text="quit"
#string comparison
if [[ $text = "quit" ]]; then
    echo "Variable matches"
fi

#number comparison
if [ $numb -eq 5 ]; then
    echo "$numb equals 5"
fi

# select loop
PS3="Choose your option [number]: "
select option in "Battle" "Surrender" "Help"; do
    echo "You selected $option" 
    break
done

# case loop
read -p "Podaj literę: " letter

case $letter in
    [a-z]) echo "Lower case";;
    [A-Z]) echo "Upper case";;
    *) echo "Other sign ";;
esac

#date and time
current_date=$(date +"%Y-%m-%d")
echo "Current date is: $current_date"