CC=gcc


proc_fan: runsim.c 
	$(CC) -std=c99  -o proc_fan runsim.c  
