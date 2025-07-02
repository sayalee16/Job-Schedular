// main.c
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "./fcfs/fcfs.h"
#include "./sjf_np/sjf_np.h"
#include "./sjf_p/sjf_p.h"
#include "./priority_np/priority_np.h"
#include "./priority_p/priority_p.h"
#include "./round_robin/round_robin.h"

int main(int argc, char *argv[])
{
    FILE *fp = stdin;

    if (argc == 2)
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("Error opening input file");
            return 1;
        }
    }

    int n;
    fscanf(fp, "%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        fscanf(fp, "%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    // fcfs(processes, n);
    // sjf_non_preemptive(processes, n);
    // sjf_preemptive(processes, n);
    // priority_non_preemptive(processes, n);
    // priority_preemptive(processes, n);
    round_robin(processes, n, 2); // Assuming time quantum of 2 for round robin

    free(processes);

    fclose(fp);

    return 0;
}
