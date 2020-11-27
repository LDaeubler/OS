#include <unistd.h>  //fork
#include <sys/wait.h>  // wait
#include <sys/types.h> //pid_t
#include <stdio.h>   // printf
#include <stdlib.h>   // exit

/* Pfad zum Programm ggf. anpassen */
#define  PROGRAM "./task"
#define  FAIL -1
#define SUCCESS 0

/*
   Posix-Schema
*/
int main (void) {
   printf("Entering parent %d (PID)\n", getpid());
   pid_t pid;
   // Die Switch Anweisung wird in zwei Prozessen ausgeführt.
   switch (pid = fork() ) {   // fork() liefert PID vom Kind. 
   case -1:                   // Es Gab einen Fehler, kein Prozess erstellt
      perror("fork()");       // Fehlerausgabe auf der Console
      return FAIL;
   case 0:                    // Er befindet sich im Kind Prozess
      printf("Entering child %d (PID)\n", getpid());
      execlp (PROGRAM, PROGRAM, "arg_0", "arg_1", NULL); // Neuen Programm-Code für das Kind laden
      printf("Failure execlp ...\n");  // -> wird eigentlich nie erreicht! Fehlerausgabe
      break;      
   default: // Man ist im Eltern Prozess, dieser bekommt die ID des Kindprozesses
      //if (wait(NULL) != pid) {
	   if (waitpid (pid, NULL, 0) != pid) {
          perror ("waitpid()");
          return FAIL;
       }
   }
   return SUCCESS;
}
