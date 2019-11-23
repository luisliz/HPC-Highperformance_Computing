from pyspark import SparkContext, SparkConf 
import timeit
import threading

conf = SparkConf()
conf.setAppName("Word count")
sc = SparkContext(conf=conf)

rdd = sc.textFile("sherlock.txt")

words = rdd.flatMap(lambda line: line.split('\n')).collect() 

rss = sc.parallelize(words).map(lambda word: (word, 1)).collect()

compact = {}
for element, count in rss:
    if element in compact: 
        compact[element] += count
    else: 
        compact[element] = count

f = open("res.txt", "w+")
for i in sorted(compact): 
    strr = "%s: %d\n" % (i,  compact[i])
    f.write(strr.encode('utf-8'))
f.close()

sc.stop()
#elapsed_time = timeit.timeit(run_spark, number=1)
#print "Elapso timo", elapsed_time
