import org.apache.spark._
import org.apache.spark.SparkContext._

object WordCount {
    def main(args: Array[String]) {
      val inputFile = args(0)
      val outputFile = args(1)
      val conf = new SparkConf().setAppName("wordCount")
      conf.setMaster("local[8]")
      // Create a Scala Spark Context.
      val sc = new SparkContext(conf)
      // Load our input data.
      val input =  sc.textFile(inputFile)
      println(textFile.count())
      // Split up into words.
      val words = textFile.flatMap(line => line.split(" ")).map(word => (word, 1)).reduceByKey((a,b) => a+b)
      words.collect()
    }
}
