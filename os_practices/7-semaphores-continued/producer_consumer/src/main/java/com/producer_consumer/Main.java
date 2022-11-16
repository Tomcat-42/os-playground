package com.producer_consumer;

import com.producer_consumer.*;

import java.util.concurrent.*;

public class Main {
  private static final int SIZE = 10;
  private static CircularSet serials = new CircularSet(1000);
  private static ExecutorService exec = Executors.newCachedThreadPool();
  private static int waitTime = 10;

  /*
   * Classe anonima, que solicita numeros para o SerialNumberGenerator, e verifica
   * se o valor retornado já foi obtido por alguma Thread
   */
  static class SerialChecker implements Runnable {

    public void run() {
      while (true) {
        try {
          int serial = SerialNumberGenerator.nextSerialNumber();
          if (serials.contains(serial)) {
            System.out.println("Duplicate: " + serial);
            System.exit(0);
          }
          serials.add(serial);
        } catch (InterruptedException e) {
          System.out.println("Interrupted");
        }
      }
    }
  }

  public static void main(String[] args) throws Exception {
    for (int i = 0; i < SIZE; i++)
      exec.execute(new SerialChecker());

    exec.shutdown();

    TimeUnit.SECONDS.sleep(waitTime);
    System.out.println("Nenhum número duplicado detectado");
    System.exit(0);

  }

  // public static void main(String[] args) {
  // Sync sc = new Sync();
  //
  // Thread t1 = new Thread(new Worker(sc));
  // Thread t2 = new Thread(new Worker(sc));
  // Thread t3 = new Thread(new Worker(sc));
  // Thread t4 = new Thread(new Worker(sc));
  // Thread t5 = new Thread(new Worker(sc));
  //
  // t1.start();
  // t2.start();
  // t3.start();
  // t4.start();
  // t5.start();
  //
  // }

}
