package com.luis 

import org.apache.spark._
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext._
import org.apache.spark.sql.SparkSession 

object WordCount {
  def main(args: Array[String]) {
    val inputFile = args(0)
    val outputFile = args(1)
    //val conf = new SparkConf().setAppName("wordCount")
    //conf.setMaster("local[8]")
    //
    val sc = SparkSession.builder.appName("Word Count").getOrCreate() 
    // Create a Scala Spark Context.
    //val sc = new SparkContext(conf)
    // Load our input data.
    val input =  sc.read.textFile(inputFile)
    println(input.count())
    // Split up into words.
    val words = input.flatMap(line => line.split(" ")).map(word => (word, 1)).reduceByKey((a,b) => a+b)
    words.collect()
  }
}
