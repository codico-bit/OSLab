#include <stdio.h>
/*
Simple Round Robin scheduler:
1. Take n processes with arrival time (AT) and burst time (BT)
2. Take time quantum (tq)
3. For each time slice:
   - Give tq time to each process that has arrived
   - If process needs <= tq, complete it
   - If process needs > tq, give tq and move to next
4. For each completed process:
   - Completion time (CT) = time when process finishes
   - Turnaround time (TAT) = CT - AT
   - Waiting time (WT) = TAT - BT
5. Print process details and averages
*/
struct p {
    int id, at, bt, ct, tat, wt, rt;
};

int main() {
    int n, tq, t = 0, done = 0;
    float atat = 0, awt = 0;
    struct p a[10];
    
    printf("Enter n and time quantum: ");
    scanf("%d %d", &n, &tq);
    
    for(int i = 0; i < n; i++) {
        printf("P%d AT BT: ", i+1);
        a[i].id = i+1;
        scanf("%d %d", &a[i].at, &a[i].bt);
        a[i].rt = a[i].bt;
    }
    
    printf("\nP\tAT\tBT\tCT\tTAT\tWT");
    while(done < n) {
        for(int i = 0; i < n; i++) {
            if(a[i].rt > 0 && a[i].at <= t) {
                if(a[i].rt <= tq) {
                    t += a[i].rt;
                    a[i].ct = t;
                    a[i].rt = 0;
                    done++;
                    
                    a[i].tat = a[i].ct - a[i].at;
                    a[i].wt = a[i].tat - a[i].bt;
                    atat += a[i].tat;
                    awt += a[i].wt;
                    printf("\nP%d\t%d\t%d\t%d\t%d\t%d", 
                        a[i].id, a[i].at, a[i].bt, a[i].ct, a[i].tat, a[i].wt);
                } else {
                    t += tq;
                    a[i].rt -= tq;
                }
            }
        }
    }
    
    printf("\nAvg TAT: %.2f\nAvg WT: %.2f\n", atat/n, awt/n);
    return 0;
} 