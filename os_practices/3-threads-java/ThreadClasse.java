public class ThreadClasse extends Thread {
  public ThreadClasse(){
    super();
  }

  public void run(){
    for (int i=0; i <20;i++){
    System.out.println("Thread["+
    Thread.currentThread().getName()+ "]="+i);
}
