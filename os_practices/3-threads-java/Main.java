import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
public class Main {
  public static void main(String[] args) {
    // TODO code application logic here

    // Exercicio 1 Cached
    ExecutorService executor= Executors.newCachedThreadPool();

    // Exercicio 2 fixed 5
    //ExecutorService executor= Executors.newFixedThreadPool(5);

    // Exercicio 3 fixed 2
    //ExecutorService executor= Executors.newFixedThreadPool(2);

    for (int i=0; i < 1000; i++){
      executor.execute(new ThreadInterface());
    }

    
    System.out.println("Threads executando");
    executor.shutdown();
  }
}
