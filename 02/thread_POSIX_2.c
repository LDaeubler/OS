#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Übergabe mehrerer unterschiedlich getypter Parameter
struct thread_data{
   int  thread_id;
   float  sum;
   char message[20];
};

void *perform_work(void *arguments){
	struct thread_data *my_data;
  my_data = (struct thread_data *) arguments;
	printf("THREAD DATA --> %d, %f, %s\n", my_data->thread_id, my_data->sum, my_data->message);
	// data manipulation
	// strcpy(my_data->message, "XXX");
  strcat(my_data->message, "XXX"); // Strings verketten (anhängen)
}

int main(void) {
  pthread_t threads[NUM_THREADS];
  struct thread_data thread_data_array[NUM_THREADS];
  int i;
  int result_code;
   
  //create all threads one by one
  for (i = 0; i < NUM_THREADS; i++) {
    printf("IN MAIN: Creating thread %d.\n", i);
    thread_data_array[i].thread_id = i;
    thread_data_array[i].sum = 36.0;
    strcpy(thread_data_array[i].message, "TestMessage");
    // hand over multiple parameters by struct
	  result_code = pthread_create(&threads[i], NULL, perform_work, &thread_data_array[i]);
    assert(!result_code);
  }

  printf("IN MAIN: All threads are created.\n");

  //wait for each thread to complete
  for (i = 0; i < NUM_THREADS; i++) {
    result_code = pthread_join(threads[i], NULL);
    assert(!result_code);
    printf("IN MAIN: Thread %d has ended.\n", i);
  }
  
  // whatch the thread results
  for (i = 0; i < NUM_THREADS; i++) {
    printf("Thread %d results: %s\n", i, thread_data_array[i].message);
  }
  printf("MAIN program has ended.\n");
  return 0;
}
