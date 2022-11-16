package com.producer_consumer;

class Sync {
  static int N;

  public Sync() {
    N = 0;
  }

  public synchronized void methodSync() throws Exception {
    {
      N++;
      if (N < 5) {
        wait();
        System.out.println("Saindo do wait " + Thread.currentThread().getName());
      } else {
        // notifyAll();
        notify();
      }

    }
  }

}
