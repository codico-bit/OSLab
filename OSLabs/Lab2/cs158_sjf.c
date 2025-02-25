#include<stdio.h>
/*
Overall summary:
Declare process structure, 
Declare read for process structure
In main, 
- take input on number of processes
- take input on arrival time, burst time, and priority for each process
- calculate appropriate completion time for each process and update all processes
- with at bt ct you can calculate rest, so do those for all and print it

*/
struct proc { int no, at, bt, ct, tat, wt; };
struct proc read(int i) {
    struct proc p = {i}; 
    printf("\nProcess No: %d\nEnter Arrival Time and Burst Time: "); 
    scanf("%d %d", &p.at, &p.bt); 
    return p; 
}
int main() {
    int n; 
    float avgtat = 0, avgwt = 0; 
    struct proc p[10]; 
    printf("<--SJF Scheduling Algorithm (Non-Preemptive)-->\nEnter Number of Processes: "); 
    scanf("%d", &n); 
    for(int i = 0; i < n; i++) p[i] = read(i + 1);

    // Calculate completion time without sorting
    int currentTime = 0;
    int remaining = n; // Initialize remaining processes count
    while(remaining > 0) {
        int minIndex = -1;

        for(int j = 0; j < n; j++) {
            if(p[j].at <= currentTime && p[j].ct == 0) {
                if (minIndex == -1 || p[j].bt < p[minIndex].bt) {
                    minIndex = j; // find the first process that has arrived and not completed
                }
            }
        }

        if(minIndex != -1) {
            currentTime += p[minIndex].bt; // Update current time
            p[minIndex].ct = currentTime; // Set completion time
            remaining--; // Decrement remaining processes count
        } else {
            currentTime++; // If no process is ready, increment time
        }
    }

    printf("\nProcess\t\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at; 
        p[i].wt = p[i].tat - p[i].bt; 
        avgtat += p[i].tat; 
        avgwt += p[i].wt; 
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat / n, avgwt / n);
}