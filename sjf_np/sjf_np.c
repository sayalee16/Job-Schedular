// sjf_np.c
#include <stdio.h>
#include "sjf_np.h"
#include "../heap/heap.h"

int compareByBurstTime(Process a, Process b) {
    return a.burst_time < b.burst_time;
}

void sortByArrival(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sjf_non_preemptive(Process processes[], int n)
{
    sortByArrival(processes, n);

    MinHeap heap;
    initHeap(&heap, compareByBurstTime);

    int current_time = 0;
    int completed = 0;
    int index = 0;
    int total_wt = 0;

    printf("\nSJF Non-Preemptive Scheduling:\n");
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\n");

    while (completed < n)
    {
        while (index < n && processes[index].arrival_time <= current_time)
        {
            insertHeap(&heap, processes[index]);
            index++;
        }

        if (isHeapEmpty(&heap))
        {
            current_time++;
            continue;
        }

        Process p = extractMin(&heap);

        if (current_time < p.arrival_time)
            current_time = p.arrival_time;

        p.start_time = current_time;
        p.completion_time = current_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.start_time - p.arrival_time;

        current_time = p.completion_time;
        total_wt += p.waiting_time;
        completed++;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p.pid, p.arrival_time, p.burst_time,
               p.start_time, p.completion_time,
               p.turnaround_time, p.waiting_time);
    }
    float avg_wt = (float)total_wt / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
}
