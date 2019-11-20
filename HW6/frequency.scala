import scala.collection.immutable.WrappedString; 
import scala.collection.Map
import org.apache.spark.SparkContext
import org.apache.spark.SparkConf

case class DoctTerms(filename:String, terms:Map[String, Int]) 

class studyClass {
  def tokenize(line: String): Array[String] = new WrappedString(line).toLowerCase().split(' ')

  def study(filename:String):DocTerms = {
    val conf = new SparkConf().setMaster("local[*").setAppName("simple-app")
    val sc= new SparkContext(conf)

    val counts = (sc.textFile(filename).flatMap(tokenize).map((s:String) => (s,1))
      .reduceByKey( _ + _ )
      .collectAsMap())
    DocTerms(filename, counts)
  }
}

object Main {

  def main() {
    val stc = new studyClass
    val book1 = stc.study("/home/cc/Highperformance_Computing/HW6/sherlockShort.txt")

    for(c<-book1.terms.slice(20)) println(c)
  }

}
