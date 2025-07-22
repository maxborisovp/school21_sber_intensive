#!/bin/bash
if [ "$#" -ne 1 ]
then
   echo "Error, you must put file name"
   exit 1
fi

File="$1"

if [ ! -f "$File" ]
then
    echo "Error! file doesnt exist"
    exit 1
fi

if [ ! -s "$File" ]
then
    echo "Error! file mustnt be empty"
    exit 1
fi

num_records=$(wc -l < "$File")
num_unique=$(awk -F' - ' '{print $1}' "$File"| sort -u | wc -l)
num_hash_changes=$(awk -F' - ' '{print $4}' "$File"| sort -u | wc -l)

echo "$num_records $num_unique $num_hash_changes"
