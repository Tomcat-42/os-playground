import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
public class Main {
  public static void main(String[] args) {
    // TODO code application logic here
    ExecutorService executor=
    Executors.newCachedThreadPool();
    for (int i=0; i < 5; i++){
      executor.execute(new ThreadInterface());
    }
    System.out.println("Threads executando");
    executor.shutdown();
  }
}
