#!/bin/bash 
python3 generateGraph.py $1
gcc -fopenmp allAlgos.c -lm -o algos && ./algos $1 
