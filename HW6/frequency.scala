import scala.collection.immutable.WrappedString; 
import scala.collection.Map
import org.apache.spark.SparkContext
import org.apache.spark.SparkConf

//class DocTerms(filename:String, terms:Map[String, Int]) {
//  val filename = filename
//  val terms = terms
//}
object Main {
  //def tokenize(line: String): Array[String] = new WrappedString(line).toLowerCase().split(' ')

//  def study(filename:String):DocTerms = { 
//    val conf = new SparkConf().setMaster("local[*]").setAppName("simple-app")
//    val sc= new SparkContext(conf)
//    
//    val counts = (sc.textFile(filename).flatMap(tokenize).map((s:String) => (s,1))
//        .reduceByKey( _ + _ )
//        .collectAsMap())
//    val dt = new DocTerms(filename, counts)
//
//    dt
//  }
//
  def main() {
    val text = sc.textFile("mytextfile.txt")
 val counts = text.flatMap(line => line.split(" ")).map(word => (word,1)).reduceByKey(_+_) counts.collect
    //for(c<-book1.terms.slice(20)) println(c)
  }

}
