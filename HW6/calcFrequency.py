from pyspark import SparkContext, SparkConf 
import timeit
import re

def printResults(inpDict):
    for w in inpDict.keys(): 
        print(w, ": ", inpDict[w])

def countWords(l): 
    result = {}
    l = l.split(' ') 
    for j in l:
        j = j.lower()
        if j in result: 
            result[j] += 1
        else: 
            result[j] = 1 
    return result 

def run_spark(): 
    conf = SparkConf()
    conf.setAppName("Word count")
    sc = SparkContext(conf=conf)
    
    rdd = sc.textFile("sherlock.txt")
    
    result = {} 
    lines = rdd.flatMap(lambda line: line.split('\n')).collect()
    res = sc.parallelize(lines).map(lambda line: countWords(line)).collect()
    
    for group in res:
        result.update(group) 
    
    sc.stop()

elapsed_time = timeit.timeit(run_spark, number=1)
print("Elapso timo ", elapsed_time)
