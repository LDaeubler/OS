#include <stdio.h>
#include <windows.h>
#include <assert.h>
/* WINAPI ?????
The way the name is decorated depends on the language and how the compiler is 
instructed to make the function available, that is, the calling convention. 
The standard inter-process calling convention for Windows used by DLLs is known as the WinAPI 
convention. It is defined in Windows header files as WINAPI, which is in turn 
defined using the Win32 declarator __stdcall.
*/

// Deklaration der Methode
DWORD WINAPI MyThreadProc(LPVOID lpParameter); // LP -> 32Bit Pointer, für kompatibilität für alte Betriebssystemen

//void ErrorHandler(LPTSTR lpszFunction);

typedef struct  {
	int val1;
	float val2;
	char text[20];
} PARAM;

int main(void)
{
	DWORD dwThreadID; //ungarische Notation mit Typenkürzel
	HANDLE hThread;

	//lokale Parameter-Variable, STACK
	PARAM stack = {10, 20.0, "MESSAGE"};
	
	// dynamische HEAP-Variable
	PARAM *pHeap = malloc(sizeof(PARAM));
	pHeap->val1 = 10;
	pHeap->val2 = 20.0;
	strcpy(pHeap->text, "MESSAGE");
	
	
	printf("Creating Thread: \n");
	hThread = CreateThread( 
        NULL,               // default security attributes
        0,                  // use default stack size  
        MyThreadProc,       // thread function name
        //&stack,          	// argument to thread function - STACK Version 
		pHeap,				// argument to thread function - HEAP Version
        0,                  // use default creation flags 
        &dwThreadID			// returns the thread identifier 
	);
	assert(hThread != NULL);

	// WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	WaitForSingleObject(hThread, INFINITE);
	// WaitForSingleObject(hThread, 200);
	   
	CloseHandle(hThread);
	
	return 0;
}

DWORD WINAPI MyThreadProc(LPVOID lpParameter)
{
	printf("Entering MyThreadProc, Parameter Adress: %p\n", lpParameter);
	assert(lpParameter != NULL);
	PARAM *pData = (PARAM *) lpParameter;
	// printf is NOT thread safe --> chaotic Terminal Output possible
	//-> es schreiben mehrer threads auf einer Konsole
	// Sleep(500);
	printf("--- passed data: %d ", pData->val1);
	printf("%.4f ", pData->val2);
	printf("%s", pData->text);
	return 0;
}

