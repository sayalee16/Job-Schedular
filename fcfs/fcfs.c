// fcfs.c
#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"
#include "../queue/queue.h"
#include "../process.h"

void merge(Process arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    Process *L = (Process *)malloc(n1 * sizeof(Process));
    Process *R = (Process *)malloc(n2 * sizeof(Process));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i].arrival_time <= R[j].arrival_time)
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Process arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void sortByArrivalTime(Process processes[], int n)
{
    mergeSort(processes, 0, n - 1);
}

void fcfs(Process processes[], int n)
{
    sortByArrivalTime(processes, n);

    Queue q;
    initQueue(&q);

    // Enqueue all processes in arrival order
    for (int i = 0; i < n; i++)
    {
        enqueue(&q, processes[i]);
    }

    int current_time = 0;
    int total_wt = 0;
    int i = 0;

    printf("\nFCFS Scheduling (with Queue):\n");
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\n");

    while (!isEmpty(&q))
    {
        Process p = dequeue(&q);

        if (current_time < p.arrival_time) //	Is CPU idle and waiting for the process? cuz no p in ready q
            current_time = p.arrival_time;

        p.start_time = current_time;
        p.completion_time = current_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.start_time - p.arrival_time;

        total_wt += p.waiting_time;
        current_time = p.completion_time;

        // Display results
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p.pid, p.arrival_time, p.burst_time,
               p.start_time, p.completion_time,
               p.turnaround_time, p.waiting_time);
    }
    float avg_wt = (float)total_wt / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
}