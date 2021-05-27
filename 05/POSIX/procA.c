#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>	    // ftruncate
#include <sys/mman.h>	// shm_open, mmap
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include "shared_mem.h"

int main(void)
{
	int file_des = shm_open("/test2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR ); 
    printf("--- file des %i \n", file_des);
	assert(file_des != -1);
    
	int status = ftruncate(file_des, sizeof(struct TEST));
    assert (status != -1);
    
    struct TEST *shm = mmap(NULL, sizeof(struct TEST),
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED, file_des, 0);
    assert (shm != MAP_FAILED);

	shm->size = BUFSIZE; // lasst sich bestimmt noch etwas intelligenter ermitteln ... 
    int i = 0;
    while (i < 20) {
    	int count = i % shm->size;
    	char buf[20];
    	printf("Bitte int eingeben: ");
    	gets(buf);
    	shm->numbers[count] = atoi(buf);
    	i++;
	}
	shm_unlink("/test2");
}
 