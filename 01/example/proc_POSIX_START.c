#include <unistd.h>  //fork
#include <sys/wait.h>  // wait
#include <sys/types.h> //pid_t
#include <stdio.h>   // printf
#include <stdlib.h>   // exit

/* Pfad zum Programm ggf. anpassen */
#define  PROGRAM "./step.exe"
#define  FAIL -1
#define SUCCESS 0

int main (void) {
   pid_t pid;
   int child_stat = 0;
   switch (pid = fork ()) {
   case -1:
      perror("fork()");
      return FAIL;
   case 0:
       execlp (PROGRAM, PROGRAM, "10", "22", NULL);
       printf("Failure execlp ...\n");
       break;      
   default:
       if (waitpid (pid, &child_stat, 0) != pid) {
          perror ("waitpid()");
          return FAIL;
       }
   }
   printf("child %d terminated with exit status %d", pid, WEXITSTATUS(child_stat));
   return SUCCESS;
}
