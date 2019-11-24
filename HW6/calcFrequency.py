from pyspark import SparkContext, SparkConf 
from time import time

def printResults(inpDict):
    for w in inpDict.keys(): 
        print(w, ": ", inpDict[w])

conf = SparkConf()
conf.setAppName("Word count")
sc = SparkContext(conf=conf)

rdd = sc.textFile("sherlock2.txt")

result = {} 
lines = rdd.flatMap(lambda line: line.split(' ')).map(lambda word: (word, 1)).reduceByKey(lambda a, b: a + b)
t0 = time()
res = lines.collect()
print("time {}s".format(time()-t0))

sc.stop()
