#include <stdio.h>
#include <stdlib.h>


int main (int argc , char* argv[])
{
	int i = 0;
	int start = atoi(argv[1]);
	int end = atoi(argv[2]);
	for (i = start; i <= end; i++)
		printf("%i ",i);
	// Win OS --> not allowed!
	// system("pause");
	return 46; 
}
