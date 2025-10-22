Author: Maya Francis
Date: 22/10/2025

To compile: gcc scheduler.c -o scheduler
To run: ./scheduler

There are no special instructions needed to run the program otherwise. 

It is set to run fcfs as is, but can be scheduled to run either by commenting out one of sjf(processes, n); OR fcfs(processes,n); in main(), the one not commented out is what will run.
Then, just to get the correct labelling of the output, in the line print(n, processes, 1); the 1 is signalling fcfs, and 0 is signalling sjf;
depending on which you want to run, switch the 1 to a 0 or vice versa.
