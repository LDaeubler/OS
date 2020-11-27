#include <windows.h>	// CreateProcess, WaitForSingleObject, CloseHandle
#include <stdio.h>	// printf
#include <string.h>  //memset

/* Pfad zum Programm ggf. anpassen */
#define  PROGRAM "./task.exe"
#define  FAIL -1
#define SUCCESS 0
#define TIME 3000


int main( void )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

    // getCurrentProcessID
    printf("my Process ID %d\n", GetCurrentProcessId());
	
	// Start the child process. 
    if( !CreateProcess( PROGRAM,   // module name!!! 
        "arg1 arg2",        	// No Command line, parameters
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        ABOVE_NORMAL_PRIORITY_CLASS,              // 
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return FAIL;
    }
    if (GetPriorityClass(pi.hProcess) == ABOVE_NORMAL_PRIORITY_CLASS)
    	printf("--child with ABOVE_NORMAL_PRIORITY_CLASS\n");

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE);
	
    
	// Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    
    return SUCCESS;
}

