from pyspark import SparkContext, SparkConf 
from operator import add 

conf = SparkConf()

conf.setMaster("local")
conf.setAppName("Word count") #[*] is number of cores
sc = SparkContext(conf=conf)
sc.setLogLevel("WARN")

rdd = sc.textFile("sherlockShort.txt")

docs = rdd.flatMap(lambda doc: doc.split(' '))

print(docs.map(lambda word: (word, 1)).reduceByKey(add))
#counts = sc.parallelize(textFile)

#sortd = rdd.flatMap(lambda word: [(word, 1)]).collect()
#print(sortd)
