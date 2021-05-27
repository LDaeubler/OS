#include <windows.h>
#include <stdio.h>
// #include <conio.h>
// #include <tchar.h>
// #pragma comment(lib, "user32.lib")

#define BUF_SIZE 256
char szName[] = "Global\\MyFileMappingObject";

int main()
{
   HANDLE hMapFile;
   char* pBuf;

   hMapFile = OpenFileMapping(
                   FILE_MAP_READ,   // read/write access
                   FALSE,                 // do not inherit the name
                   szName);               // name of mapping object

   if (hMapFile == NULL)
   {
      printf("Could not open file mapping object (%d).\n",
             GetLastError());
      return 1;
   }

   pBuf = (LPTSTR) MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_READ,  // read/write permission
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

   //MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
   printf("Shared Memory Content: %s\n", pBuf);
   char buf[10];
   gets(buf);
    
   UnmapViewOfFile(pBuf);
   CloseHandle(hMapFile);

   return 0;
}
