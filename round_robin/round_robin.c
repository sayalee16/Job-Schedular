#include <stdio.h>
#include "round_robin.h"
#include "../queue/queue.h"
#include "../Gantt.h"

GanttEntry gantt[1000]; // assuming max 1000 context switches
int g_index = 0;

void round_robin(Process processes[], int n, int time_quantum)
{
    Queue q;
    initQueue(&q);

    int current_time = 0;
    int completed = 0;
    int index = 0;
    float total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
        processes[i].completion_time = 0;
    }

    printf("\nRound Robin Scheduling (TQ = %d):\n", time_quantum);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    // push first process if it has arrived at time 0
    while (index < n && processes[index].arrival_time <= current_time)
    {
        enqueue(&q, processes[index]);
        index++;
    }

    while (!isEmpty(&q) || completed < n)
    {
        if (isEmpty(&q))
        {
            // no process ready → advance time
            current_time++;
            while (index < n && processes[index].arrival_time <= current_time)
            {
                enqueue(&q, processes[index]);
                index++;
            }
            continue;
        }

        Process p = dequeue(&q);

        if (!p.started)
        {
            p.start_time = current_time;
            p.started = 1;
        }

        int run_time = (p.remaining_time < time_quantum) ? p.remaining_time : time_quantum;

        gantt[g_index].pid = p.pid;
        gantt[g_index].start_time = current_time;
        gantt[g_index].end_time = current_time + run_time;
        g_index++;

        p.remaining_time -= run_time;
        current_time += run_time;

        // add newly arrived processes during this run
        while (index < n && processes[index].arrival_time <= current_time)
        {
            enqueue(&q, processes[index]);
            index++;
        }

        if (p.remaining_time == 0)
        {
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;

            total_wt += p.waiting_time;
            completed++;

            // update the original array
            for (int i = 0; i < n; i++)
            {
                if (processes[i].pid == p.pid)
                {
                    processes[i] = p;
                    break;
                }
            }
        }
        else
        {
            enqueue(&q, p); // not finished → reinsert
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

    printf("\nGantt Chart:\n");
    for (int i = 0; i < g_index; i++)
    {
        printf("| P%d ", gantt[i].pid);
    }
    printf("|\n");

    printf("%d", gantt[0].start_time);
    for (int i = 0; i < g_index; i++)
    {
        printf("    %d", gantt[i].end_time);
    }
    printf("\n");
}
