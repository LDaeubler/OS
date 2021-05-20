#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

int main (int argc, char *argv[])
{
	//printf("Entering Child ID: %d", GetCurrentProcessId( ));
	printf("param c %d param v %s\n", argc, argv[0]);
	printf("Please Input Character: ");
	char x = getc(stdin);
	return x;
}

