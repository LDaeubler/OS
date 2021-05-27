#include <windows.h>
#include <stdio.h>
//  #include <conio.h>
// #include <tchar.h>

#define BUF_SIZE 256
char szName[] = "Global\\MyFileMappingObject";
char szMsg[] = "Message from first process.";

int main()
{
    HANDLE hMapFile;
    char* pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        printf("Could not create file mapping object (%d).\n",
            GetLastError());
        return 1;
    }
    pBuf = (char*) MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        printf("Could not map view of file (%d).\n",
            GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }
   
    strcpy(pBuf, szMsg);
    char buf[10];
    printf("press button");
    gets(buf);
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
