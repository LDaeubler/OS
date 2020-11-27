
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>


int main (int argc, char *argv[])
{
	// getCurrentProcessID
    // printf("my Process ID %d\n", GetCurrentProcessId());
	
	printf("arguments count: %d\n", argc);
	printf("arguments: \n");
	
	int i;
	for (i = 0; i < argc; i++)
		printf("--- %s\n", argv[i]);
	printf("Please Input Character: ");
	
	char x = getc(stdin);
	return x;
}
