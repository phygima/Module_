#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <num1> <num2>"
    exit 1
fi

a=$1
b=$2

result=$((a + b))
echo "$1 + $2 = $result"
