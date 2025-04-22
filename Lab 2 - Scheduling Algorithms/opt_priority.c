#include <stdio.h>
/*
Simple Priority scheduler (non-preemptive):
1. Take n processes with arrival time (AT), burst time (BT), and priority (PRI)
2. Sort by arrival time first
3. Among processes that have arrived:
   - Pick the one with highest priority (lower number = higher priority)
   - Execute it completely (non-preemptive)
4. For each process:
   - Completion time (CT) = max(previous CT, current AT) + BT
   - Turnaround time (TAT) = CT - AT
   - Waiting time (WT) = TAT - BT
5. Print process details and averages
*/
struct p {
    int id, at, bt, ct, tat, wt, pri;
};

int main() {
    int n, i, j, min;
    float atat = 0, awt = 0;
    struct p a[10], t;
    
    printf("Enter n: ");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        printf("P%d AT BT PRI: ", i+1);
        a[i].id = i+1;
        scanf("%d %d %d", &a[i].at, &a[i].bt, &a[i].pri);
    }
    
    // Sort by arrival time
    for(i = 0; i < n-1; i++)
        for(j = 0; j < n-i-1; j++)
            if(a[j].at > a[j+1].at) {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
    
    // Find process with highest priority among arrived processes
    for(min = 0; a[min].at == a[0].at && min < n; min++)
        if(a[min].pri < a[0].pri)  // Lower number = higher priority
            t = a[0], a[0] = a[min], a[min] = t;
    
    a[0].ct = a[0].at + a[0].bt;
    
    // For remaining processes
    for(i = 1; i < n; i++) {
        for(min = i; min < n && a[min].at <= a[i-1].ct; min++)
            if(a[min].pri < a[i].pri)  // Lower number = higher priority
                t = a[i], a[i] = a[min], a[min] = t;
        
        a[i].ct = (a[i].at > a[i-1].ct) ? a[i].at + a[i].bt : a[i-1].ct + a[i].bt;
    }
    
    printf("\nP\tAT\tBT\tPRI\tCT\tTAT\tWT");
    for(i = 0; i < n; i++) {
        a[i].tat = a[i].ct - a[i].at;
        a[i].wt = a[i].tat - a[i].bt;
        atat += a[i].tat;
        awt += a[i].wt;
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d", 
            a[i].id, a[i].at, a[i].bt, a[i].pri, a[i].ct, a[i].tat, a[i].wt);
    }
    
    printf("\nAvg TAT: %.2f\nAvg WT: %.2f\n", atat/n, awt/n);
    return 0;
} 