package com.producer_consumer;

import com.producer_consumer.Semaphore;

public class SerialNumberGenerator {
  private static volatile Semaphore sem = new Semaphore(1);
  private static volatile int serialNumber = 0;

  public static int nextSerialNumber() throws InterruptedException {
    sem.acquire();
    int tmp = serialNumber++;
    sem.release();

    return tmp; // Not thread-safe
  }
}
