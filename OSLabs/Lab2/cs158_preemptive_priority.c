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
- initialize current time
- while there are remaining processes, 
    - find the process with the highest priority
    - increment current time at every single step, since you can switch the processes
    - since its preempative
    - update the remaining processes
*/
struct proc {
    int no, at, bt, rt, ct, wt, tat, priority;
};

struct proc read(int i) {
    struct proc p = {i};
    printf("\nProcess No: %d\nEnter Arrival Time, Burst Time, and Priority: ");
    scanf("%d %d %d", &p.at, &p.bt, &p.priority);
    p.rt = p.bt;
    return p;
}

int main() {
    int n, remaining, highest_priority_index, current_time;
    struct proc p[10]; // array of structures
    float avgtat = 0, avgwt = 0;

    printf("<--Highest Priority First Scheduling Algorithm (Preemptive)-->\nEnter Number of Processes: ");
    scanf("%d", &n); // take input on number of processes
    for (int i = 0; i < n; i++) p[i] = read(i + 1);

    for (int i = 0; i < n - 1; i++) // sort based on arrival time
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                struct proc temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }
    current_time = p[0].at + 1; // initialize current time

    remaining = n;
    while (remaining > 0) {
        highest_priority_index = -1; // to store the index of the process with highest priority
        for (int j = 0; j < n; j++)
            if (p[j].at <= current_time && (highest_priority_index == -1 || p[j].priority > p[highest_priority_index].priority)) // check if process has arrived and has highest priority
                highest_priority_index = j;

        if (highest_priority_index != -1) {
            p[highest_priority_index].ct = current_time++; // you are incrementing current time at every single step, since you can switch the processes
            // since its preempative
            p[highest_priority_index].rt--;
            if (p[highest_priority_index].rt == 0) {
                p[highest_priority_index].priority = MIN;
                remaining--;
            }
        }
    }

    printf("\nProcessNo\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avgtat += p[i].tat;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat / n, avgwt / n);
}