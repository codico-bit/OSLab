#include <stdio.h>
/*
Simple FCFS (First Come First Serve) scheduler:
1. Take n processes with arrival time (AT) and burst time (BT)
2. Sort them by arrival time
3. Execute in order of arrival
4. For each process:
   - Completion time (CT) = max(previous CT, current AT) + BT
   - Turnaround time (TAT) = CT - AT
   - Waiting time (WT) = TAT - BT
5. Print process details and averages
*/
struct p {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n, i, j;
    float atat = 0, awt = 0;
    struct p a[10], t;
    
    printf("Enter n: ");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        printf("P%d AT BT: ", i+1);
        a[i].id = i+1;
        scanf("%d %d", &a[i].at, &a[i].bt);
    }
    
    // Sort by arrival time
    for(i = 0; i < n-1; i++)
        for(j = 0; j < n-i-1; j++)
            if(a[j].at > a[j+1].at) {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
    
    // Calculate completion time
    a[0].ct = a[0].at + a[0].bt;
    for(i = 1; i < n; i++)
        a[i].ct = (a[i].at > a[i-1].ct) ? a[i].at + a[i].bt : a[i-1].ct + a[i].bt;
    
    printf("\nP\tAT\tBT\tCT\tTAT\tWT");
    for(i = 0; i < n; i++) {
        a[i].tat = a[i].ct - a[i].at;
        a[i].wt = a[i].tat - a[i].bt;
        atat += a[i].tat;
        awt += a[i].wt;
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", a[i].id, a[i].at, a[i].bt, a[i].ct, a[i].tat, a[i].wt);
    }
    
    printf("\nAvg TAT: %.2f\nAvg WT: %.2f\n", atat/n, awt/n);
    return 0;
} 