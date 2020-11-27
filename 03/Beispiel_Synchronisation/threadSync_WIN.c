#include <stdio.h> 
#include <windows.h>

#define _2_SEC 2000
#define _1_SEC 1000

int *pHeap;
HANDLE ghSemaphore;

DWORD WINAPI threadA(LPVOID arg)
{
	while (1) {
		WaitForSingleObject(ghSemaphore, INFINITE);
		*pHeap = *pHeap + 1;
		ReleaseSemaphore(ghSemaphore, 1, NULL);
		Sleep(_2_SEC);
	}
}

DWORD WINAPI threadB (LPVOID arg)
{
	HANDLE *pHandleThreadA = (HANDLE*) arg;
	while (1) {
		printf("threadB, *pHeap: %d\n", *pHeap);
		WaitForSingleObject(ghSemaphore, INFINITE);
		if (*pHeap > 34) {
			ReleaseSemaphore(ghSemaphore, 1, NULL);
			TerminateThread(*pHandleThreadA, 0x00FF); //some EXIT_CODE, not specified
			ExitThread(0x00FF); 
		}
		ReleaseSemaphore(ghSemaphore, 1, NULL);
		Sleep(_1_SEC);
		
	}
}

void main(void)
{
	// mem allocation on process heap
	pHeap = (int*) malloc(sizeof(int));
	*pHeap = 17;
	
	HANDLE hTA, hTB;
    DWORD dwTA_ID, dwTB_ID;
	
	ghSemaphore = CreateSemaphore( 
        NULL,           // default security attributes
        1,  // initial count
        3,  // maximum count
        NULL);          // unnamed semaphore
    
	hTA = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        threadA, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &dwTA_ID); // receive thread identifier
    
    hTB = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        threadB, 
        &hTA,       // pointer to threadA-Handle
        0,          // default creation flags
        &dwTB_ID); // receive thread identifier
	
	WaitForSingleObject(hTA, INFINITE);
	WaitForSingleObject(hTB, INFINITE);

    CloseHandle(hTA);
	CloseHandle(hTB);
    CloseHandle(ghSemaphore);
    
    return;		
}
