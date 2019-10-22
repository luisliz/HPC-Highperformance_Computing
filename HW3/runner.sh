#!/bin/bash 
python3 generateGraph.py $1
gcc allAlgos.c -o algos && ./algos $1 
