package com.producer_consumer;


public class Producer implements Runnable {
  IBuffer buffer;

  public Producer(IBuffer buffer) {
    this.buffer = buffer;
  }

  public void run() {
    for (int i = 0; i < 1000; i++) {
      buffer.put(i);
      System.out.println("Produced: " + i);
    }
  }
}
