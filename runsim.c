#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// This is for implementing makearg.. Might put on a seperate file and put overhead her//e
//int makeargv(const char *, const char *, char ***);// makearg


int main (int argc, char *argv[]) {

  pid_t childpid = 0;
  int i, n, c;
  int pr_count = 0;
  int numtokens;
  FILE *fp;
  char delim[] = " ";
  char ** myargv;
//char err[80];


  fp = fopen("testing.data");
    if(fp == NULL){
       perror("Error opening file");
       return(-1);
     }

  if (argc != 2) {
    fprintf(stderr, "Usage: %s processes\n", argv[0]);
    return 1;
  }
  while ((c = getopt(argc, argv, "n")) != -1) {
    switch (c) {
    case 'n':
        /* option n is the max number of processes generated*/
        int pr_limit = atoi(optarg);
                                             break;
    case 'h':
        fprintf("Here is a list of commands:n\";
     default:
         perror("proc_fan: Error: Detailed error message" );
        exit;
  }

 n = atoi(argv[1]);//** Maybe use pr_limit instead of n
  for(i = 1; i < n; i++){
    if((childpid = fork()) <= 0){
      pr_count++;
    }
      break;
   }
 while(argv[2] != '\0'){

     if(pr_count == pr_limit){

        fprintf(stderr, "Need to wait for child process. Reached limit");
        wait(NULL);
        pr_count--;
      }

     //read a line from standad imput (fgets) up to MAX_CANNON
     //execute program by forking a child
     //(fork, makeargv, execvp)
        childpid = fork();
        if(childpid == -1){
           printf("Can't fork the process\n");
           return 0;
         }
     }
