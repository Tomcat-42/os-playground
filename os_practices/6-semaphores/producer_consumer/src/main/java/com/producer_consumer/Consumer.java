package com.producer_consumer;

public class Consumer implements Runnable {
  IBuffer buffer;

  public Consumer(IBuffer buffer) {
    this.buffer = buffer;
  }

  public void run() {
    for (int i = 0; i < 1000; i++) {
      int item = buffer.get();
      System.out.println("Consumed: " + item);
    }
  }
}
