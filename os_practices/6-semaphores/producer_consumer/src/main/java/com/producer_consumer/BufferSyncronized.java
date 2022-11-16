package com.producer_consumer;

/** Hello world! */
public class BufferSyncronized implements IBuffer {
  volatile int count;
  volatile int in, out, N;
  int[] buffer;
  Object sync_lock = new Object();

  public BufferSyncronized(int _N) {
    buffer = new int[_N];
    N = _N;
    in = 0;
    out = 0;
    count = 0;
    sync_lock = new Object();
  }

  public void put(int item) {
    while (count == N) {
      // do nothing
    }
    buffer[in] = item;
    in = (in + 1) % N;

    synchronized (sync_lock) {
      count++;
    }
  }

  public int get() {
    int item;
    while (count == 0) {
      // do nothing
    }
    item = buffer[out];
    out = (out + 1) % N;
    synchronized (sync_lock) {
      count--;
    }
    return item;
  }
}
