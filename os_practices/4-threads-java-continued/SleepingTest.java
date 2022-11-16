import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class SleepingTest implements Runnable{
  boolean setYield= false;

  public SleepingTest (boolean _setYield){
    this.setYield= _setYield;
  }

  public void run() {
    for (int i=0; i <10;i++) {
      System.out.println("Thread["+Thread.currentThread().getName()+"]="+i);
      if (setYield) {
        Thread.yield();
      }
    }
  }

  public static void main(String[] args) {
    ExecutorService exec = Executors.newCachedThreadPool();
    exec.execute(new SleepingTest(true));
    exec.execute(new SleepingTest(true));
    exec.execute(new SleepingTest(false));
    exec.execute(new SleepingTest(false));
    exec.shutdown();
  }
}
