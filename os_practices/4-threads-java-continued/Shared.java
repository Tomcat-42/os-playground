import java.util.concurrent.TimeUnit;


class Data {
  volatile int valor;
  // getter
  int get() { return valor; }
  // setter
  void set(int v) { valor = v; }
}


class MyThread implements Runnable {
  Data data;
  int id;
  MyThread(Data d, int i) {
    data = d;
    id = i;
  }
  public void run() {
    // for (int i = 0; i < 100; i++) {
    //   int v = data.get();
    //   data.set(v + 1);
    // }
    data.valor = 20;
    System.out.println(data.valor);
  }
}

public class Shared {
  public static void main(String[] args) {
    Data data = new Data();
    Thread t1 = new Thread(new MyThread(data, 1));
    Thread t2 = new Thread(new MyThread(data, 2));
    try {
      t1.start();
      TimeUnit.MILLISECONDS.sleep(3);
      t2.start();
      t1.join();
      t2.join();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    System.out.println(data.get());
  }
}
