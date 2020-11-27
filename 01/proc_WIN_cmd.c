#include <windows.h>	// CreateProcess, WaitForSingleObject, CloseHandle
#include <stdio.h>	// printf
#include <string.h>  //memset

/* Pfad zum Programm ggf. anpassen */
#define  PROGRAM "task asdf asdf asdf" // task.exe -> wird ausgeführt
#define  FAIL -1
#define SUCCESS 0
#define TIME 5000

int main( void )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

    printf("my Process ID %d\n", GetCurrentProcessId());
	
	// Start the child process. 
    if( !CreateProcess( NULL,   // No module name (use command line)
        PROGRAM,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return FAIL;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    
    return SUCCESS;
}

