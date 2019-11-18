from pyspark import SparkContext, SparkConf 

conf = SparkConf().setAppName("local[*]").getOrCreate() #[*] is number of cores
sc = SparkContext(conf=conf)

distFile = sc.textFile("sherlock.txt")
