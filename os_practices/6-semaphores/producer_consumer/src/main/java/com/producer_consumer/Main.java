package com.producer_consumer;

import com.producer_consumer.*;

public class Main {
  public static void exec_buffer(IBuffer b) {
    Producer p = new Producer(b);
    Consumer c = new Consumer(b);
    Thread t1 = new Thread(p);
    Thread t2 = new Thread(c);
    t1.start();
    t2.start();
    try {
      t1.join();
      t2.join();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    // System.out.println("Normal Buffer");
    // exec_buffer(new Buffer(10));

    // System.out.println("ReentrantLock(Mutex) Buffer");
    // exec_buffer(new BufferReentrantLock(10));

    System.out.println("Semaphore Buffer");
    exec_buffer(new BufferSemaphore(10));
  }

}
