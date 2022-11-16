import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ThreadCallable implements Callable<Integer> {
  private static Random generator = new Random();

  public Integer call() {
    return generator.nextInt(1000);
  }
}

public class MainCallable {
  public static void main(String[] args) {
    ExecutorService executor = Executors.newCachedThreadPool();
    ArrayList<Future<Integer>> resultados = new ArrayList<Future<Integer>>();

    for (int i = 0; i < 10; i++) resultados.add(executor.submit(new ThreadCallable()));
    executor.shutdown();
    for (int i = 0; i < resultados.size(); i++) {
      try {
        Future<Integer> result;
        result = resultados.get(i);
        System.out.println(result.get());
      } catch (InterruptedException ex) {
        ex.printStackTrace();
      } catch (ExecutionException ex) {
        ex.printStackTrace();
      }
    }
  }
}
