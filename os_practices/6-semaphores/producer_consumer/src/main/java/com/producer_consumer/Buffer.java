package com.producer_consumer;

/** Hello world! */
public class Buffer implements IBuffer {
  volatile int count;
  volatile int in, out, N;
  int[] buffer;

  public Buffer(int _N) {
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
    count++;
  }

  public int get() {
    int item;
    while (count == 0) {
      // do nothing
    }
    item = buffer[out];
    out = (out + 1) % N;
    count--;
    return item;
  }

  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
