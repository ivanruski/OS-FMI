#!/bin/bash

declare -A morse_to_char

while read letter morse; do
        morse_to_char[$morse]=$letter
done < morse

touch morse_to_char.txt

while IFS='' read line; do
    echo ${morse_to_char[$line]} >> morse_to_char.txt
done < <(sed -e 's/\s/\n/g' secret_message)

awk 'BEGIN { c="" } { c=c$0 } END { print c }' morse_to_char.txt > encrypted 

sed -r -i -e 's/(.)/\L\1/g' encrypted

rm morse_to_char.txt
