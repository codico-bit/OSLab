#include <stdio.h>
/*
Overall summary:
Declare process structure, 
Declare read for process structure
In main, 
- take input on number of processes
- take input on arrival time, burst time, and priority for each process
- sort based on arrival time
- while there are remaining processes, 
    - if the process has remaining time to execute, handle it
    - else the process has no remaining time to execute, update values and print it remaining processes
*/
struct proc { int no, at, bt, ct, tat, wt, rt; };
struct proc read(int i) {
    struct proc p = {i}; 
    printf("\nProcess No: %d\nEnter Arrival Time: "); 
    scanf("%d", &p.at); 
    printf("Enter Burst Time: "); 
    scanf("%d", &p.bt); 
    p.rt = p.bt; 
    return p; 
}
int main() {
    struct proc p[10]; 
    float avgtat = 0, avgwt = 0; 
    int n, tq, ct = 0, remaining; 
    printf("<--Round Robin Scheduling Algorithm-->\nEnter Number of Processes: "); 
    scanf("%d", &n); 
    printf("Enter Time Quantum: "); 
    scanf("%d", &tq); 
    for (int i = 0; i < n; i++) p[i] = read(i + 1);
    for (int i = 0; i < n - 1; i++) // sorted based on arrival time
        for (int j = 0; j < n - i - 1; j++) 
            if (p[j].at > p[j + 1].at) { struct proc tmp = p[j]; p[j] = p[j + 1]; p[j + 1] = tmp; }
    
    remaining = n; 
    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWT\n");
    
    int i = 0; // Initialize index
    while (remaining != 0) {
        if (p[i].rt > 0) {
            if (p[i].rt <= tq) {
                ct += p[i].rt; 
                p[i].rt = 0; 
            } else {
                p[i].rt -= tq; 
                ct += tq; 
            }
            if (p[i].rt == 0) {
                remaining--; 
                p[i].ct = ct; 
                p[i].tat = p[i].ct - p[i].at; 
                avgtat += p[i].tat; 
                p[i].wt = p[i].tat - p[i].bt; 
                avgwt += p[i].wt; 
                printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
            }
        }
        i = (i + 1) % n; // Loop back round robin
        while (p[i].at > ct) { // Wait for the next process to arrive
            i = (i + 1) % n;
        }
    }
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat / n, avgwt / n);
}