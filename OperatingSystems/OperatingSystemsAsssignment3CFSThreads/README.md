# Operating Systems Assignment 3: Completely Fair Thread Scheduler

This program is a simple implementation of the Completely Fair Scheduler using threads.

The producer thread opens an input text file (currently hardcoded to ass3Input.txt) containing the scheduling type, priority, and expected execution time of various processes and reads them into 3 different ready queues for 4 different CPU threads.  Each CPU thread has 3 queues; 1 RQ0 for processes with priority 0 - 99, 1 RQ1 for processes with priority 100 - 129, and 1 RQ2 for processes with priority 130 - 139.  Each CPU will be initialized with 1 FIFO process, 1 RR process, and 3 normal processes.  

The consumer thread iterates through each of its local RQs and exhausts them of all its processes, running each one based on its scheduling policy.

To run the program, the script must be compiled and run, for example:
gcc cfs_threads.c -o assignment3
./assignment3

 
