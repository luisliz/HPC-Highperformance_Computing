#!/bin/bash
spark-submit calcFrequency.py --num-executors 1 >> touch.txt
spark-submit calcFrequency.py --num-executors 2 >> touch.txt
spark-submit calcFrequency.py --num-executors 4 >> touch.txt
spark-submit calcFrequency.py --num-executors 8  >> touch.txt
spark-submit calcFrequency.py --num-executors 12 >> touch.txt
spark-submit calcFrequency.py --num-executors 16 >> touch.txt
spark-submit calcFrequency.py --num-executors 20 >> touch.txt
spark-submit calcFrequency.py --num-executors 40 >> touch.txt
