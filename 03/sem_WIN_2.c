#include <windows.h>
#include <stdio.h>
#include <assert.h>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 12
#define BUF 200

HANDLE ghSemaphore;
char history [THREADCOUNT] [BUF] = { 0 };

DWORD WINAPI ThreadProc( LPVOID );

int main( void )
{
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;
    

    //
    // Create a semaphore with initial and max counts of MAX_SEM_COUNT
    ghSemaphore = CreateSemaphore( 
        NULL,           // default security attributes
        MAX_SEM_COUNT,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore

    assert(ghSemaphore != NULL);
    // Create worker threads
    for(i = 0; i < THREADCOUNT; i++ ) {
        aThread[i] = CreateThread( 
                     NULL,       // default security attributes
                     0,          // default stack size
                     ThreadProc, 
                     &history[i], // history of thread wait routines
                     0,          // default creation flags
                     &ThreadID); // receive thread identifier

        assert(aThread[i] != NULL );
    }
    // Wait for all threads to terminate
    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Close thread and semaphore handles
    for(i = 0; i < THREADCOUNT; i++ )
        CloseHandle(aThread[i]);

    CloseHandle(ghSemaphore);
    // print thread history
    for (i = 0; i < THREADCOUNT; i++) {
        printf("%s \n", history[i]);
    }  
    return 0;
}

DWORD WINAPI ThreadProc( LPVOID lpParam )
{
    DWORD dwWaitResult; 
    BOOL bContinue=TRUE;
    char* threadHistory = (char*)  lpParam;
    Sleep(5);
        
    while(bContinue)
    {
        int len = strlen(threadHistory);
        assert(len < BUF);
        // Try to enter the semaphore gate.
        dwWaitResult = WaitForSingleObject( 
            ghSemaphore,   // handle to semaphore
            3L);           // zero-second time-out interval

        switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
                // TODO: Perform task
                // printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                threadHistory[len] = 'x'; // wait successfull
                threadHistory[len + 1] = '\0'; // terminate with 0

                bContinue=FALSE;            

                // Simulate thread spending time on task
                Sleep(50);

                // Release the semaphore when task is finished
                ReleaseSemaphore( 
                        ghSemaphore,  // handle to semaphore
                        1,            // increase count by one
                        NULL		// not interested in previous count
				);
                break; 
            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT: 
                // printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                threadHistory[len] = 'o'; // wait successfull
                threadHistory[len + 1] = '\0'; // terminate with 0
                break; 
        }
    }   
    return TRUE;
}
