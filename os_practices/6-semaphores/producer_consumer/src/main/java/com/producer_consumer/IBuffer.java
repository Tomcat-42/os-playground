package com.producer_consumer;

interface IBuffer {
  void put(int item);

  int get();
}
