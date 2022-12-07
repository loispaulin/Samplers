#!/bin/zsh

for i in {1..1024} ; do
    ./cmake-build-release/myRank1 -s ${i} -c -n 256 -o /Users/lpaulin/Documents/Projects/Thesis/FiguresPython/data/rank1_dir${i}.dat
done