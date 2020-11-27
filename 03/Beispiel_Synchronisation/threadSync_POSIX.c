#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int *pHeap;
sem_t sem;

void *threadA (void* arg)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while (1) {
		sem_wait(&sem);
		*pHeap = *pHeap + 1;
		sem_post(&sem);
		sleep(2);
	}
}

void *threadB (void* arg)
{
	pthread_t *pIdA = (pthread_t*) arg;
	while (1) {
		printf("threadB, *pHeap: %d\n", *pHeap); // ist doch außerhalb von sem_wait?
		sem_wait(&sem);
		if (*pHeap > 34) {
			sem_post(&sem);
			pthread_cancel(*pIdA);
			pthread_exit(NULL);
		}
		sem_post(&sem);
		sleep(1);
	}
}

void main(void)
{
	// mem allocation on process heap
	pHeap = (int*) malloc(sizeof(int));
	*pHeap = 17;
	
	sem_init(&sem, 0, 1);
	
	pthread_t idA, idB;
	
	pthread_create(&idA, NULL, threadA, NULL);
	pthread_create(&idB, NULL, threadB, &idA);
	
	pthread_join(idA, NULL);
	pthread_join(idB, NULL);
		
}
