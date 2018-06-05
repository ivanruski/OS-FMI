#!/bin/bash

function change_key {
    declare -i index
    declare -i shift_index

    shift_index=$1
    for (( i=0; i<${#alphabet}; i++ )); do
         ((index=(shift_index + i) % ${#alphabet}))
         letter_to_key["${alphabet:$i:1}"]="${alphabet:$index:1}"
         key_to_letter["${alphabet:$index:1}"]="${alphabet:$i:1}"
    done
}

function encrypt_cipher_keyword {
    keyword=$1
    read encrypted_key <\
        <( for (( i=0; i<${#keyword}; i++)); do
                echo -n "${letter_to_key[${keyword:$i:1}]}"
           done )
}

declare -A letter_to_key
declare -A key_to_letter
declare alphabet
read alphabet < <(echo {a..z} | tr -d ' ')

declare encrypted_key;
declare -i key
for (( j=0; j<${#alphabet}; j++ )); do
    ((key= $j))
    change_key "${key}" 
    encrypt_cipher_keyword "fuehrer"

    if grep -q "$encrypted_key" encrypted
    then 
       echo $key
       while read line; do 
            echo -n "${key_to_letter[${line}]}"
       done < <(sed -r -e 's/(.)/\1\n/g' -e 's/.$//' encrypted)
       echo ""  
       exit 0
    fi
done
