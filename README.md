# OS.1
Project 1
Maria Wydick

Overview: This project is a simple representation of a batch processing facility and it is 
represented by a C program named runsim.c . It expands on another program found on the Unix
Systems Programming textbook and it represents a fan of processes.

runsim.c runs simultaneous processes by calling fork() in a while loop and states how many processes 
can run simultaneously. It also keeps count of active children and once there are as many children(processes)
as the limit states of processes (pr_limit==pr_count), the program must wait() for a child. 

I understand this project to be like  a queue of processes but there is a limit of processes on 
each iteration so once that limit is reached, the program needs to wait for one of the children 
to finish in order to continue. This is repeated until there is nothing else on stdin which in our case is 
a txt file named testing.data.

