#!/bin/bash
if [ "$#" -ne 3 ]
then
   echo "Error, not 3 peremenn"
   exit 1
fi

PathF="$1"
str1="$2"
str2="$3"

if [ ! -f "$PathF" ]
then
    echo "Error! file doesnt exist"
    exit 1
fi

if [ ! -s "$PathF" ]
then
    echo "Error! file mustnt be empty"
    exit 1
fi

if [ -z "$str1" ]
then
    echo "Error! string mustnt be empty"
    exit 1
fi

if [ -z "$str2" ]
then
    echo "Error! string mustnt be empty"
    exit 1
fi

sed -i '' "s/$str1/$str2/g" "$PathF"

f_size=$(stat -f%z "$PathF")
f_data=$(stat -f'%Sm' -t '%Y-%m-%d %H:%M' "$PathF")
f_shasum=$(shasum -a 256 "$PathF" | awk '{print $1}')
echo "$PathF - $f_size - $f_data - $f_shasum - sha256" >> src/files.log
