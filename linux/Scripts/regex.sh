#!/bin/bash

#standard comparison in [[ ... ]] used * ? [abc]

fruit="banana"
if [[ $fruit == b* ]]; then # contains b and random string after
    echo "$fruit starts with 'b'"
fi

# full regular expression used =~ and 
: '
    Regex operators in bash
    ^ - start of string 
    $ - end of string
    . - random sign
    * - zero or more previous sign occuration
    + - one  or more ...   
    ? - zero or one p
    [] - group of signs ex: [a-z] - small letters
    | - or, ex: (apple|banana) 
'

place="kanion"
#starts with letter
if [[ $place =~ ^k* ]]; then
    echo "$place starts with 'k'"
fi

#end with letter
if [[ $place =~ .*n$ ]]; then
    echo "$place ends with 'n'"
fi

number=515
if [[ $number =~ ^[0-9]{3} ]]; then
    echo "$number contains 3 numbers"
fi

# advanced concpets 
: '
    Used of [] () {} 
    [] - create class of signs, can adjust one any sign from the set
        [abc] -a| b |c
        [a-z] - only lowercase sign
        [0-5]- only numbers from 0 to 5
        [^a-z] - negation of lowercase so - any sign but not lowercase letter

    () - grouping patterns 
    (Ab)+ - occurenceof Ab one or more times in text

    {} - quantifiers - how many time should pattern occurs
        a{3} - aaa
        a{3,5} aaa - aaaaa
'

email=test.1@gmail.com
if [[ $email =~ ^[a-zA-Z0-9._]{5,20}@(gmail|example|interia){1}\.[a-z]{2,3}$ ]]; then
    echo "$email is matching pattern" 
else
    echo "$email is not matching pattern" 
fi
