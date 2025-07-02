#include <stdio.h>
#include "../heap/heap.h"
#include "priority_p.h"

int compareByPriority(Process a, Process b)
{
    if (a.priority == b.priority)
    {
        return a.arrival_time < b.arrival_time;
    }
    return a.priority < b.priority;
}

void sortByArrival(Process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
}

void priority_preemptive(Process processes[], int n)
{
    MinHeap heap;
    initHeap(&heap, compareByPriority);

    sortByArrival(processes, n);

    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
    }

    int current_time = 0, completed = 0, index = 0;
    float total_wt = 0;

    printf("\nPriority Scheduling (Preemptive):\n");
    printf("PID\tAT\tBT\tPri\tCT\tTAT\tWT\n");

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

        if (!p.started)
        {
            p.start_time = current_time;
            p.started = 1;
        }

        // Run for 1 unit
        p.remaining_time--;
        current_time++;

        if (p.remaining_time == 0)
        {
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
            completed++;

            // Write back
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
        else
        {
            insertHeap(&heap, p);
        }
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
