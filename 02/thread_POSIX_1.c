#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// beliebige Werte zwischen 1s und 10s
int sleep_time[] = {2, 6, 1, 8, 5};  // Datensegment)

void *perform_work(void *arguments){
  int index = *((int *)arguments); // arguments -> Casten -> Derefernzieren
  // int sleep_time = rand();
  
  printf("THREAD %d: Started.\n", index);
  printf("THREAD %d: Will be sleeping for %d seconds.\n", index, sleep_time[index]);
  sleep(sleep_time[index]);
  printf("THREAD %d: Ended.\n", index);
}


int main(void) {
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int i;
  int result_code;
   
  //create all threads one by one
  for (i = 0; i < NUM_THREADS; i++) {
    printf("IN MAIN: Creating thread %d.\n", i);
    thread_args[i] = i;
    result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
    assert(!result_code); // gibt eine fertige Fehlerausgabe zurück
  }

  printf("IN MAIN: All threads are created.\n");

  //wait for each thread to complete
  for (i = 0; i < NUM_THREADS; i++) {
    result_code = pthread_join(threads[i], NULL); // warten auf Thread
    assert(!result_code);
    printf("IN MAIN: Thread %d has ended.\n", i);
  }

  printf("MAIN program has ended.\n");
  return 0;
}
