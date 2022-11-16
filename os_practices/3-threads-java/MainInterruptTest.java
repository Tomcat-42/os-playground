import java.util.concurrent.TimeUnit;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainInterruptTest {
    public static void main(String[] args) throws InterruptedException {
    ExecutorService executor= Executors.newCachedThreadPool();
    for (int i=0; i < 10; i++)
      executor.execute(new MyThread());
      System.out.println("Sleeping....");
      TimeUnit.SECONDS.sleep(10);
      executor.shutdownNow();
      System.out.println("Shutdown solicitado");
    }
}

class MyThread implements Runnable{
  public void run() {
    boolean sair=false;
    while (!sair){
      System.out.println(Thread.currentThread().getName());
      if (Thread.currentThread().isInterrupted()){
        System.out.println("Interrupção solicitada, finalizando a Thread"+ Thread.currentThread().getName());
        sair= true;
      }
    }
  }
}
