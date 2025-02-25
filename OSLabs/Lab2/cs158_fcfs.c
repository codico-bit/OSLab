#include <stdio.h>
/*
Overall summary:
Declare process structure, 
Declare read for process structure
In main, 
- take input on number of processes
- take input on arrival time, burst time, and priority for each process
- sort based on arrival time
- iterate through the processes, updating their completion time, turnaround time, and waiting time
- print the results on the go itself, while updating the values
*/
struct proc { int no, at, bt, ct, tat, wt; };

struct proc read(int i) {
    struct proc p = {i};
    printf("\nProcess No: %d\nEnter Arrival and Burst Time (space-separated): ");
    scanf("%d %d", &p.at, &p.bt);
    return p;
}

int main() {
    struct proc p[10];
    float avgtat = 0, avgwt = 0;
    int n, ct = 0;
    printf("<--FCFS Scheduling Algorithm (Non-Preemptive)-->\nEnter Number of Processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) p[i] = read(i + 1);
    
    for (int i = 0; i < n - 1; i++) // sort based on arrival time
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                struct proc tmp = p[j]; p[j] = p[j + 1]; p[j + 1] = tmp;
            }
    
    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        ct += p[i].bt; 
        p[i].ct = ct;
        
        p[i].tat = p[i].ct - p[i].at; 
        avgtat += p[i].tat;
        
        p[i].wt = p[i].tat - p[i].bt; 
        avgwt += p[i].wt;
        
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].wt);
    }
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat / n, avgwt / n);
}