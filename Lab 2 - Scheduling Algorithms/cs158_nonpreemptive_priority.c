#include <stdio.h>
#define MIN -9999
/*
Overall summary:
Declare process structure, 
Declare read for process structure
In main, 
- take input on number of processes
- take input on arrival time, burst time, and priority for each process
- sort based on arrival time
- initialize remaining processes
- initialize current time
- while there are remaining processes, 
    - find the process with the highest priority
    - once you have the highest priority process, you cannot switch (non preemptive), so 
        - finish everything for this process and print it, then only go to the next process
        - ie update everything for this process and print it
- keep doing till no process remains
*/
struct proc { int no, at, bt, ct, wt, tat, pri, status; };

struct proc read(int i) {
    struct proc p = {i};
    printf("\nProcess No: %d\nEnter Arrival Time, Burst Time, and Priority (space-separated): ");
    scanf("%d %d %d", &p.at, &p.bt, &p.pri);
    p.status = 0;
    return p;
}

int main() {
    int n, ct = 0, remaining;
    struct proc p[10];
    float avgtat = 0, avgwt = 0;

    printf("<--Highest Priority First Scheduling Algorithm (Non-Preemptive)-->\nEnter Number of Processes: ");
    scanf("%d", &n); // take input on number of processes
    for (int i = 0; i < n; i++) p[i] = read(i + 1); // take input

    for (int i = 0; i < n - 1; i++) // bubble sort based on arrival time
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                struct proc temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }

    p[9].pri = MIN; remaining = n; // initialize remaining processes
    printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\tRT\n");

    ct = p[0].at; // Initialize current time
    while (remaining != 0) {
        int highest_priority_index = -1; // Initialize highest priority index to -1
        for (int i = 0; i < n; i++) // find the process with highest priority
            if (p[i].at <= ct && p[i].status != 1 && (highest_priority_index == -1 || p[i].pri > p[highest_priority_index].pri))
                highest_priority_index = i;
        // once you have the highest priority process, you cannot switch (non preemptive), so 
        // finish everything for this process and print it, then only go to the next process
        p[highest_priority_index].ct = ct += p[highest_priority_index].bt;
        p[highest_priority_index].tat = p[highest_priority_index].ct - p[highest_priority_index].at; avgtat += p[highest_priority_index].tat;
        p[highest_priority_index].wt = p[highest_priority_index].tat - p[highest_priority_index].bt; avgwt += p[highest_priority_index].wt;
        
        p[highest_priority_index].status = 1; remaining--;

        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[highest_priority_index].no, p[highest_priority_index].at, p[highest_priority_index].bt, p[highest_priority_index].pri, p[highest_priority_index].ct, p[highest_priority_index].tat, p[highest_priority_index].wt, p[highest_priority_index].wt);
    }

    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat / n, avgwt / n);
}