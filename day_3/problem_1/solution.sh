#!/bin/bash

for line in $(rg -o 'mul\(\d+,\d+\)' $1); do
    echo $line | tr -d "mul()" | tr ',' '\t'
done | awk '{total += $1 * $2} END {print total}'
