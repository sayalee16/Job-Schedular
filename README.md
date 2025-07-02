# Job Scheduling Simulator in C

This project implements core CPU scheduling algorithms such as FCFS, SJF (preemptive and non-preemptive), Priority Scheduling (preemptive and non-preemptive), and Round Robin. It leverages fundamental data structures like queues and min-heaps to simulate realistic scheduling behavior, making it a robust and modular DSA-based simulation in C.

## Algorithms Implemented
- FCFS
- SJF (Preemptive & Non-preemptive)
- Priority Scheduling (Preemptive & Non-preemptive)
- Round Robin

## Technical Highlights
-  **Queue** → FCFS, Round Robin  
-  **Min Heap** → SJF, Priority Scheduling  
-  **Sorting** → To arrange processes by Arrival Time, Burst Time, or Priority  
-  **File Handling** → Accepts input from an external file

## Compile and Run
```bash
gcc main.c fcfs/fcfs.c queue/queue.c -o scheduler
