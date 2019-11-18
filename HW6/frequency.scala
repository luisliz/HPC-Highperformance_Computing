import scala.collection.immutable.WrappedString; 
import scala.collection.Map

def tokenize(line: String): Array[String] = 
  new WrappedString(line).toLowerCase().split(' ')

case class DoctTerms(filename:String, terms:Map[String, Int])

def study(filename:String):DocTerms = {
  val counts = (sc.textFile(filename).flatMap(tokenize).map((s:String) => (s,1))
    .reduceByKey( _ + _ )
    .collectAsMap())
  DocTerms(filename, counts)
}

val book1 = study("/home/cc/Highperformance_Computing/HW6/sherlockShort.txt")

for(c<-book1.terms.slice(20)) println(c)
