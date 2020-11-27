#include <windows.h> //CreateSemaphore, CreateThread, WaitForSingleObject, CloseHandle, ReleaseSemaphore
#include <stdio.h> //printf, fprint, fgets, fclose, fopen
#include <assert.h>

// !!!!! Prozess global 
CRITICAL_SECTION gCS;

DWORD WINAPI reader( LPVOID );
DWORD WINAPI writer( LPVOID );

int main( void )
{
    HANDLE hT1, hT2;
    DWORD dwT1ID, dwT2ID;
    int i;
    

    // Create a Crit. Sect. Object
    InitializeCriticalSection(&gCS);
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
    DeleteCriticalSection(&gCS);
    return 0;
}

DWORD WINAPI reader(LPVOID lpParam )
{
    DWORD dwWaitResult;
	printf("--- Entering reader\n");
    ///////////////////// critical section
    EnterCriticalSection(&gCS);
	// file read
    assert(dwWaitResult == WAIT_OBJECT_0);
	FILE* pFile = fopen(".\\test\\file.txt", "r" );
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
    
    Sleep(500);
    LeaveCriticalSection(&gCS);
    /////////////////////  end critical section
}

DWORD WINAPI writer( LPVOID lpParam )
{
    DWORD dwWaitResult;
	printf("--- Entering writer\n");
    ///////////////////// critical section
    EnterCriticalSection(&gCS);
	// file read
    assert(dwWaitResult == WAIT_OBJECT_0);
	FILE* pFile = fopen(".\\test\\file.txt", "w" );
    assert (pFile != NULL);
    int i;
    for (i = 0; i < 30000; i++)
        	fprintf(pFile, "%d Was Du heute kannst besorgen, das verschiebe nicht auf morgen!\n", i);
    fclose(pFile);  
    
    Sleep(500);
    LeaveCriticalSection(&gCS);
	/////////////////////  end critical section
}

