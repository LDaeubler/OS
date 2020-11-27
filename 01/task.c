
#include <windows.h> // GetCurrentProcessId() -> nicht Betriebssystem Unabhängig
#include <stdio.h>
#include <stdlib.h>


/*
	Wenn der Task Betriebssystem unabhängig ist.
	Sollte eine main enthalten, damit dies als neuer Prozess gestartet werden kann.
	-> Executables müssen voll kompiliert werden und anschließend als Prozess ausgeführt werden.
*/

int main (int argc, char *argv[]) // Anzahl und Werte der Parameter   Array von Pointern -> H'A'L'L'O'(Nullterminierung)
{
	printf("-----  task -----\n");
	
    printf("my Process ID %d\n", GetCurrentProcessId()); // getCurrentProcessID
	
	printf("arguments count: %d\n", argc);
	
	int i;
	for (i = 0; i < argc; i++)
	{
		printf("Argument %d: ",i);
        printf(argv[i]);
        printf("\n");
	}
	printf("Please Input Character: ");
	
	//char x = getc(stdin);
	char x = getchar();
	printf("%c\n",x);
	printf("-----  task Ende -----\n");
	return x;
}
