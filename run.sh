#!/bin/bash

threads=$1
mode=$2

# group is threads minus 1
group=$(($threads - 1))

numaoption="0-$group"

# run the program
numactl --physcpubind=$numaoption --membind=0 ./main -t $threads -m $mode -n 20
