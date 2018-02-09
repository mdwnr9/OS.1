#include <stdio.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define MAX_CANON 30	

int makeargv(char *s, char *delimiters, char ***argvp);



int main (int argc, char *argv[]) {
  printf("In proc_fan\n");

  pid_t childpid = 0;
  int i, n;
  char c;
  int pr_limit;  
  int pr_count = 0;
  int numtokens;
  char delim[] = " ";
  char ** myargv;
  char str[MAX_CANON+1];
//char err[80];

  
  
 /* if (argc != 2	) {
    fprintf(stderr, "Usage: %s processes\n", argv[0]);
    return 1;
    }*/

  while ((c = getopt(argc, argv, "n:h")) != -1) {
    switch (c) {
    case 'n':
        /* option n is the max number of processes generated*/
        pr_limit = atoi(optarg);
        break; 
    case 'h':
	printf("Here is a list of commands");
        break;
    case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
     default:
         perror("proc_fan: Error: Detailed error message" );
	exit;
     }
   }

        //While we haven't reached end of line
        while(fgets(str, MAX_CANON, stdin) != NULL){

               //If pr_limit is equal to pr_counter, wait for child to finish
               //Decrement the pr_count
               if(pr_count == pr_limit){
                  fprintf(stderr, "Reached the limit, process count = %i, limit = %i\n\n", pr_count, pr_limit);
                  wait(NULL);
                  pr_count--;
                  fprintf(stderr, "Child finished! Running next command\n");
              }

             
                //fgets(str, MAX_CANON, stdin); //This is for reading the commands from stdin into string, str up to MAX_CANON chars   
            
             //**TEST. Remove before submission**
         /*    numtokens = makeargv(str,delim, &myargv);
             printf("Testing outs\n");
             int j = 0;
             for (j = 0; j < numtokens; j++){ 
             printf("%s\n",myargv[j]);
             }*/
            // TERMINATING HERE
            //      return 0;
          
                 fprintf(stderr, "Current process count = %i, limit = %i\n\n", pr_count, pr_limit);
            

             //Execute the program
             //by forking a child (fork, makeargv, execvp)
             childpid = fork();
                if(childpid == 0){
                    printf("This is a child process");
                     makeargv(str, delim, &myargv);//  
                     execvp(myargv[0], &myargv[0]);
                        printf("Exec failed\n");
                         exit(1);
                 }

          //increment counter to keep track of active children... Keep it here?
            pr_count++;

 
   //Is this necessary here??... This was on 3.2 code.
    fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
          i, (long)getpid(), (long)getppid(), (long)childpid);
    }
 
    //Check to see if any of the children have finished(waitpid)
    //with WNOHANG option. Decrement pr_counter
      int status;
      while(waitpid(0, &status, WNOHANG) != 0){
           
            pr_count--;
      }  

      //After encountering EOF on stdin
      //Wait for the rest of children
      //to finish; then exit
       while(wait(NULL) > 0);// or if(EOF && wait(NULL) <= 0)break;???*****
   										

  return 0;
}

int makeargv(char *s, char *delimiters, char ***argvp)
{
   char *t;
   char *snew;
   int numtokens;
   int i;
    /* snew is real start of string after skipping leading delimiters */
   snew = s + strspn(s, delimiters);
                              /* create space for a copy of snew in t */
   if ((t = calloc(strlen(snew) + 1, sizeof(char))) == NULL) {
      *argvp = NULL;
      numtokens = -1;
   } else {                     /* count the number of tokens in snew */
      strcpy(t, snew);
      if (strtok(t, delimiters) == NULL)
         numtokens = 0;
      else
         for (numtokens = 1; strtok(NULL, delimiters) != NULL;
              numtokens++)
              ;  
                /* create an argument array to contain ptrs to tokens */
      if ((*argvp = calloc(numtokens + 1, sizeof(char *))) == NULL) {
         free(t);
         numtokens = -1;
      } else {            /* insert pointers to tokens into the array */
         if (numtokens > 0) {
            strcpy(t, snew);
            **argvp = strtok(t, delimiters);
            for (i = 1; i < numtokens + 1; i++)
               *((*argvp) + i) = strtok(NULL, delimiters);
         } else {
           **argvp = NULL;
           free(t);
         }
      }
   }   
   return numtokens;
}
