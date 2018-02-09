#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>  

int main (int argc, char *argv[]){
   int i = 0;
   
   if (argc != 3) {
    fprintf(stderr, "Usage: <sleep-time> <# of loops>");
    return 1;
   }

   int sleeptime = atoi(argv[1]);
   int loops = atoi(argv[2]);

   fprintf(stderr, "testsim %d %d Starting\n", sleeptime, loops);

   for(i = 0; i < loops; i++){
      //Message with its process ID to stderr
      fprintf(stderr, "Process ID=%li, Parent Process ID=%li, Sleep iteration=%i\n", (long)getpid(), (long)getppid(), i+1);
      sleep(sleeptime);
   }
  

 return 0;

}

