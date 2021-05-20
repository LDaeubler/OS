#include <stdio.h>  //printf, fprint, fgets, fclose, fopen
#include <pthread.h> // pthread_t, pthread_join, create, 
#include <semaphore.h> // sem_t, sem_wait, sem_post, sem_init, sem_destroy 
#include <unistd.h> //sleep
#include <assert.h>  //assert 
   

// Semaphore wird in main erzeigt und als Argument übergeben

void* writer(void* arg) 
{ 
    //wait 
    sem_t* pSem = (sem_t *) arg;
    printf("WRITER: Semaphoren Adresse %p\n", pSem);
    ///////////////////// critical section
    sem_wait(pSem); 
    printf("Entered writer critical section\n"); 
  
    // file io
    FILE* pFile = fopen(".\\file.txt", "w" );
    assert(pFile != NULL);
    int i;
    for (i = 0; i < 30000; i++)
    	fprintf(pFile, "%d Was Du heute kannst besorgen, das verschiebe nicht auf morgen!\n", i);
    fclose(pFile);  

    // wait
    sleep(1); 
    
    printf("\nJust Exiting writer critical section\n"); 
    sem_post(pSem);
    ////////////////////////////////////////
} 

void* reader(void* arg) 
{ 
    sem_t* pSem = (sem_t *) arg;
    printf("READER: Semaphoren Adresse %p\n", pSem);
    ///////////////////// critical section 
    sem_wait(pSem); 
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
	sem_post(pSem); 
	////////////////////////////////////////
} 
   
int main() 
{ 
    sem_t sem;
	sem_init(&sem, 0, 1);  // maximal 1 Zugriff
    printf("MAIN: Semaphoren Adresse %p\n", &sem);

    pthread_t t1,t2; 
    pthread_create(&t1, NULL, writer, &sem);
    pthread_create(&t2, NULL, reader, &sem);
    
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_destroy(&sem); 
    return 0; 
} 

