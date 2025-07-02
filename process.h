// process.h
#ifndef PROCESS_H
#define PROCESS_H

typedef struct
{
    int pid;
    int arrival_time;    // time when the process arrives in the ready queue
    int burst_time;      // total time required by the process to complete
    int start_time;      // time when the process starts execution
    int completion_time; // time when the process completes execution
    int turnaround_time; // total time taken from arrival to completion : CT - AT
    int waiting_time;    // total time the process has been in the ready queue : TAT - BT
    int started;         // 0 or 1 flag
    int remaining_time;  // remaining time for the process to complete
    int priority;        // priority of the process (for priority scheduling)
} Process;

#endif
