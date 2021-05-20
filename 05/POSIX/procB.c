#include <stdio.h>
#include <assert.h>
#include <unistd.h>		// ftruncate, sleep
#include <sys/mman.h>	// shm_open, mmap
#include <sys/stat.h>   /* For mode constants */
#include <fcntl.h>      /* For O_* constants */
#include "shared_mem.h"

int main(void)
{
	int file_des = shm_open("/test2", O_RDONLY | O_RDWR, 0);
    assert(file_des != -1);
    
	/*int status = ftruncate(file_des, sizeof(struct TEST));
    assert (status != -1);
    */
    
    struct TEST *shm = mmap(NULL, sizeof(struct TEST),
                                          PROT_READ,
                                          MAP_SHARED, file_des, 0);
    assert (shm != MAP_FAILED);

    int count = 0;
    while (count < 20) {
    	printf("%i) shm->numb: \n", count);
        int i = 0;
    	for (i=0; i<shm->size; i++) {
			printf(" %d ",shm->numbers[i]);
		}
        printf("\n");
		sleep(2);
        count++;
	}
	shm_unlink("/test2");
}
