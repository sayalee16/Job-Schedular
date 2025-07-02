#include <stdio.h>
#include "../heap/heap.h"
#include "priority_np.h"

int compareByPriority(Process a, Process b)
{
    // lower priority number = higher actual priority
    return a.priority < b.priority;
}

void sortByArrival(Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
}

void priority_non_preemptive(Process processes[], int n)
{
    MinHeap heap;
    initHeap(&heap, compareByPriority);

    sortByArrival(processes, n);

    int current_time = 0, index = 0, completed = 0;
    float total_wt = 0;

    printf("\nPriority Scheduling (Non-Preemptive):\n");
    printf("PID\tAT\tBT\tPri\tCT\tTAT\tWT\n");

    while (completed < n)
    {
        // Push arrived processes to heap
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
        p.waiting_time = p.turnaround_time - p.burst_time;
        current_time = p.completion_time;
        completed++;

        // Write back to array
        for (int i = 0; i < n; i++)
        {
            if (processes[i].pid == p.pid)
            {
                processes[i] = p;
                break;
            }
        }

        total_wt += p.waiting_time;
    }

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
}
