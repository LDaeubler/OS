#include <windows.h>	
#include <stdio.h>	
// Bitte anpassen an die Vezeichnisse auf Ihrem Rechner
#define FULL_PATH "C:\\Users\\id598224\\Documents\\VL\\Betriebsysteme\\src\\01\\example\\task.exe"

void main(void)
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

    
    CreateProcess("task.exe" ,   // module name, application
        NULL,        // no Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi ); // Pointer to PROCESS_INFORMATION structure
    
	printf("Process ID Parent: %d\n", GetCurrentProcessId());
	printf("Process ID Child: %d\n", pi.dwProcessId);
	
	WaitForSingleObject( pi.hProcess, 5000 );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread ); 
    
    return;
	
}
