#include <stdio.h>
#include "../heap/heap.h"
#include "sjf_p.h"

int compareByRemainingTime(Process a, Process b)
{
    return a.remaining_time < b.remaining_time;
}

void sort(Process processes[], int n)
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

void sjf_preemptive(Process processes[], int n)
{
    MinHeap heap;
    initHeap(&heap, compareByRemainingTime);

    int current_time = 0;
    int completed = 0;
    int index = 0;
    float total_wt = 0;

    sort(processes, n);

    // Init remaining_time
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
    }

    printf("\nSJF Preemptive Scheduling (SRTF):\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    while (completed < n)
    {
        // Add all arrived processes to heap
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

        // Update process (start_time only first time)
        if (!p.started)
        {
            p.start_time = current_time;
            p.started = 1;
        }

        // Run for 1 time unit
        p.remaining_time--;
        current_time++;

        // If finished
        if (p.remaining_time == 0)
        {
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
            completed++;

            // Write back results
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
            // Re-insert with updated remaining_time
            insertHeap(&heap, p);
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
}
