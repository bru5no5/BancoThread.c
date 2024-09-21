#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OPERACOES 2147483000
#define NUM_THREADS 2

double saldo;
pthread_mutex_t mutex_saldo;

void *depositos(void *arg) {
  for (int i = 0; i < NUM_OPERACOES; i++) {
    pthread_mutex_lock(&mutex_saldo);
    saldo += 5.0;
    pthread_mutex_unlock(&mutex_saldo);
  }
  return NULL;
}

void *saques(void *args) {
  for (int i = 0; i < NUM_OPERACOES; i++) {
    pthread_mutex_lock(&mutex_saldo);
    saldo -= 2.0;
    pthread_mutex_unlock(&mutex_saldo);
  }
  return NULL;
}

int main() {

  saldo = 1000.00;

  pthread_t threads[NUM_THREADS];
  pthread_mutex_init(&mutex_saldo, NULL);

  pthread_create(&threads[0], NULL, depositos, NULL);
  pthread_create(&threads[1], NULL, saques, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex_saldo);

  printf("Saldo final: %.2lf após %d operações\n", saldo, NUM_OPERACOES);

  return 0;  
}
