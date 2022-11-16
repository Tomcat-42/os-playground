package com.producer_consumer;

import java.util.concurrent.Semaphore;

/** Hello world! */
public class BufferSemaphore implements IBuffer {
  volatile int count;
  volatile int in, out, N;
  int[] buffer;
  private Semaphore full, empty, mutex;

  public BufferSemaphore(int _N) {
    buffer = new int[_N];
    N = _N;
    in = 0;
    out = 0;
    count = 0;
    full = new Semaphore(0);
    empty = new Semaphore(_N);
    mutex = new Semaphore(1);
  }

  public void put(int item) {
    try {
      full.acquire();
      mutex.acquire();
      buffer[in] = item;
      in = (in + 1) % N;
      count++;
      mutex.release();
      empty.release();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }

  public int get() {
    int item = 0;
    try {
      empty.acquire();
      mutex.acquire();
      item = buffer[out];
      out = (out + 1) % N;
      count--;
      mutex.release();
      full.release();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    return item;
  }
}
