#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Arbeitsthread wird von einem anderen thread kontrolliert (beendet).


void *perform_work(void *arguments){
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // Um Thread beenden zu können
	int count = 0;
	while (1) { // endlos schleife
  		printf("#");
  		sleep(1);
	}
}

void *control_work(void *arguments){
	pthread_t threadID = *(pthread_t *) arguments;
	// sleep(7);
	while(1)
	{
		if (getchar() == 'z') {
			printf("\nCancelling Worker");
			pthread_cancel(threadID);
			break;
		}
	}
}

int main(void) {
	int result_code;
	pthread_t workerID;
	pthread_t controllerID;
	printf("IN MAIN: Creating worker thread\n");
	result_code = pthread_create(&workerID, NULL, perform_work, NULL);
	assert(!result_code);
	
	printf("IN MAIN: Creating controller thread\n");
	result_code = pthread_create(&controllerID, NULL, control_work, &workerID);
	assert(!result_code);
	
	//wait for each thread to complete
	result_code = pthread_join(workerID, NULL);
	assert(!result_code);
	
	result_code = pthread_join(controllerID, NULL);
	assert(!result_code);
	
	return 0;
}
