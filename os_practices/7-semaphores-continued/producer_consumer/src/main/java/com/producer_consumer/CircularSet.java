package com.producer_consumer;

/**
 * A classe CircularSet é um conjunto de tamanho limitado, utilizado para
 * armazenar os números obtidos pelas Threads.
 *
 * @version 0.1
 * @author POS-UNIOESTE
 **/
class CircularSet {
  private int[] array;
  private int len;
  private int index = 0;

  public CircularSet(int size) {
    array = new int[size];
    len = size;
    /* Inicializa o conjunto com valores -1 */
    for (int i = 0; i < size; i++)
      array[i] = -1;
  }

  /**
   * Adiciona um elemento no conjunto
   *
   * @param Valor a ser inserido
   **/
  public synchronized void add(int i) {
    array[index] = i;
    // Começa a sobrepor os elementos quando o tamanho máximo é alcançado
    index = ++index % len;
  }

  /**
   * Verifica se um dado valor está contido no conjunt
   *
   * @param Valor a ser pesquisado
   * @return False se não encontrou ou True se encontrou
   **/
  public synchronized boolean contains(int val) {
    for (int i = 0; i < len; i++)
      if (array[i] == val)
        return true;
    return false;
  }

}
