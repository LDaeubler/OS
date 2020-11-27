#include <stdio.h>  //printf, fprint, fgets, fclose, fopen
#include <pthread.h> // pthread_t, pthread_join, create, 
#include <semaphore.h> // sem_t, sem_wait, sem_post, sem_init, sem_destroy 
#include <unistd.h> //sleep
#include <assert.h>  //assert


#define SEM_COUNT 2
// !!!!! globale semaphore  
// Threads teilen sich einen gemeinsames Datensegment, dort liegt die Semaphore
// Die Variable ist Prozess global
sem_t sem; 
  
void* writer(void* arg) 
{ 
    ///////////////////// critical section
    sem_wait(&sem); 
    printf("Entered writer critical section\n"); 
  
    // file io
    FILE* pFile = fopen(".\\file.txt", "w" );
    assert (pFile != NULL);
    int i;
    for (i = 0; i < 30000; i++) {
    	
    	fprintf(pFile, "%d Was Du heute kannst besorgen, das verschiebe nicht auf morgen!\n", i);
	}
    fclose(pFile);  

    // wait
    sleep(1); 
    
    printf("\nJust Exiting writer critical section\n"); 
    sem_post(&sem);
    ////////////////////////////////////////
} 

void* reader(void* arg) 
{ 
    ///////////////////// critical section -> muss geschützt werden
    sem_wait(&sem); 
    printf("Entered reader critical section\n"); 
  
    // file read
    FILE* pFile = fopen(".\\file.txt", "r" );
    assert (pFile != NULL);
    char buffer[100];
    int i;
    for (i = 0; i < 30000; i++)
    {
    	fgets(buffer, 100, pFile);
    	if ( i % 1000 == 0)
			printf("%s", buffer);
	}
    fclose(pFile);  

    //wait 
    sleep(1); 
    
    printf("\nJust Exiting reader critical section\n");
	sem_post(&sem); 
	////////////////////////////////////////
} 
  
  
int main() 
{ 
	// no mutual exclusion!!!!  
	sem_init(&sem, 0, SEM_COUNT); // 2-> Threads dürfen gleichzeitig drauf zugreifen
    pthread_t t1,t2; 
    pthread_create(&t1, NULL, writer, NULL);
    pthread_create(&t2, NULL, reader, NULL);
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_destroy(&sem); 
    return 0; 
} 

