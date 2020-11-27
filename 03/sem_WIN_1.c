
#include <windows.h>
#include <stdio.h>
#include <assert.h>

#define MAX_SEM_COUNT 1 

HANDLE ghSemaphore;

DWORD WINAPI reader( LPVOID );
DWORD WINAPI writer( LPVOID );

int main( void )
{
    HANDLE hT1, hT2;
    DWORD dwT1ID, dwT2ID;
    int i;

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT
    ghSemaphore = CreateSemaphore( 
        NULL,           // default security attributes
        MAX_SEM_COUNT,  // initial count -> Wir machen aus der Semaphore einen Mutex
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore
    assert(ghSemaphore != NULL);
    
    hT1 = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        writer, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &dwT1ID); // receive thread identifier
    assert(hT1 != NULL );
    
    hT2 = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        reader, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &dwT2ID); // receive thread identifier
    assert(hT2 != NULL );
    
    WaitForSingleObject(hT1, INFINITE);
	WaitForSingleObject(hT2, INFINITE); 

    assert(CloseHandle(hT1));
	assert(CloseHandle(hT2));
    assert(CloseHandle(ghSemaphore));
    return 0;
}

DWORD WINAPI reader( LPVOID lpParam )
{
    DWORD dwWaitResult;
	printf("--- Entering reader\n");
    ///////////////////// critical section
    dwWaitResult = WaitForSingleObject( 
            ghSemaphore,   // handle to semaphore
            INFINITE);           // zero-second time-out interval -> Man kann sogar auf Null stellen, man überprüft nur ob ob die Semaphore belegt ist
	// file read
    assert(dwWaitResult == WAIT_OBJECT_0);
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
    
    Sleep(3000);
    ReleaseSemaphore( 
		ghSemaphore,  // handle to semaphore
        1,            // increase count by one
        NULL		// not interested in previous count
	);
    /////////////////////  end critical section
}

DWORD WINAPI writer( LPVOID lpParam )
{
    DWORD dwWaitResult;
	printf("--- Entering writer\n");
    ///////////////////// critical section
    dwWaitResult = WaitForSingleObject( 
            ghSemaphore,   // handle to semaphore
            INFINITE);           // zero-second time-out interval
	// file read
    assert(dwWaitResult == WAIT_OBJECT_0);
	FILE* pFile = fopen(".\\file.txt", "w" );
    assert (pFile != NULL);
    int i;
    for (i = 0; i < 30000; i++)
        	fprintf(pFile, "%d Was Du heute kannst besorgen, das verschiebe nicht auf morgen!\n", i);
    fclose(pFile);  
    
    Sleep(3000);
    ReleaseSemaphore( 
		ghSemaphore,  // handle to semaphore
        1,            // increase count by one
        NULL		// not interested in previous count
	);
    /////////////////////  end critical section
}

