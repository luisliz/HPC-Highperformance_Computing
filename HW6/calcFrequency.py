from pyspark import SparkContext, SparkConf 
import timeit
def run_spark(): 
    conf = SparkConf()

    conf.setMaster("local[8]")
    conf.setAppName("Word count") #[*] is number of cores
    sc = SparkContext(conf=conf)
    
    rdd = sc.textFile("sherlock.txt")
    
    docs = rdd.flatMap(lambda doc: doc.split(' '))
    res = docs.map(lambda word: (word, 1)).collect()
    
    compact = {}
    for element, count in res:
        if element in compact: 
            compact[element] += count
        else: 
            compact[element] = count
    
    f = open("res.txt", "w+")
    for i in sorted(compact): 
        strr = "%s: %d\n" % (i,  compact[i])
        f.write(strr.encode('utf-8'))
    f.close()
    
    total = 0
    for element, count in res:
        total += count
    
    print "Count original: " + str(docs.count()) + " total after process: " + str(total)

elapsed_time = timeit.timeit(run_spark, number=1)
print "Elapsed time", elapsed_time
