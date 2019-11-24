#!/bin/bash
spark-submit calcFrequency.py --num-cores 1 >> touch.txt
spark-submit calcFrequency.py --num-cores 2 >> touch.txt
spark-submit calcFrequency.py --num-cores 4 >> touch.txt
spark-submit calcFrequency.py --num-cores 8  >> touch.txt
spark-submit calcFrequency.py --num-cores 16 >> touch.txt
spark-submit calcFrequency.py --num-cores 32 >> touch.txt
spark-submit calcFrequency.py --num-cores 48 >> touch.txt
