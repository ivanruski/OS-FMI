#!/bin/bash

if [[ $# -ne 2 ]]; then 
    echo "Usage: <dest-dir> <source-website>"
    exit 2
fi

if [[ ! -d $1 ]]; then 
    echo "${1} is not a directory"
    exit 1
fi

if ! wget -q --spider "${2}"; then 
    echo "Web site is not found or currently unavailable"
    exit 3
fi

wget -rnv --show-progress -P "${1}" -nH --cut-dirs=2 "${2}"

