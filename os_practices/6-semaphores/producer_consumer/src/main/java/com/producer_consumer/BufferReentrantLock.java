package com.producer_consumer;

import java.util.concurrent.locks.ReentrantLock;

/** Hello world! */
public class BufferReentrantLock implements IBuffer {
  volatile int count;
  volatile int in, out, N;
  int[] buffer;
  private ReentrantLock mutex = new ReentrantLock();

  public BufferReentrantLock(int _N) {
    buffer = new int[_N];
    N = _N;
    in = 0;
    out = 0;
    count = 0;
  }

  public void put(int item) {
    while (count == N) {
      // do nothing
    }
    buffer[in] = item;
    in = (in + 1) % N;
    mutex.lock();
    count++;
    mutex.unlock();
  }

  public int get() {
    int item;
    item = buffer[out];
    out = (out + 1) % N;
    mutex.lock();
    count--;
    mutex.unlock();
    return item;
  }
}
