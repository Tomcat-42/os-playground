package com.producer_consumer;

class Semaphore {
  private int value;

  public Semaphore(int value) {
    this.value = value;
  }

  public synchronized void acquire() throws InterruptedException {
    while (value == 0)
      wait();
    value--;
  }

  public synchronized void release() throws InterruptedException {
    value++;
    notify();
  }
}
