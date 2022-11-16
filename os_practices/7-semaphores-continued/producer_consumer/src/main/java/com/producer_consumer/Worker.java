package com.producer_consumer;

import com.producer_consumer.Sync;

class Worker implements Runnable {
  Sync sc;

  public Worker(Sync _sc) {
    sc = _sc;
  }

  public void run() {
    try {
      sc.methodSync();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
