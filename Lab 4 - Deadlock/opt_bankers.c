#include <stdio.h>
/*
Simple Banker's Algorithm for deadlock avoidance:
1. Take input:
   - Number of processes (n) and resources (m)
   - Available resources (avail)
   - Maximum need of each process (max)
   - Currently allocated resources (alloc)
2. Calculate:
   - Need matrix = Max - Allocation
3. For each process:
   - Find a process whose needs can be satisfied
   - Mark it as done and add its resources to available
   - Repeat until all processes are done
4. If all processes complete, system is in safe state
5. Print safe sequence if found
*/

#define N 5  // processes
#define M 3  // resources

int main() {
    int i, j, k, flag;
    int alloc[N][M], max[N][M], need[N][M];
    int avail[M], work[M], finish[N], seq[N];
    
    printf("Enter allocation matrix:\n");
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            scanf("%d", &alloc[i][j]);
            
    printf("Enter maximum matrix:\n");
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            scanf("%d", &max[i][j]);
            
    printf("Enter available resources:\n");
    for(i = 0; i < M; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }
    
    // Calculate need matrix
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    
    // Initialize finish array
    for(i = 0; i < N; i++)
        finish[i] = 0;
    
    // Find safe sequence
    int count = 0;
    while(count < N) {
        flag = 0;
        for(i = 0; i < N; i++) {
            if(!finish[i]) {
                for(j = 0; j < M; j++)
                    if(need[i][j] > work[j])
                        break;
                
                if(j == M) {
                    for(k = 0; k < M; k++)
                        work[k] += alloc[i][k];
                    seq[count++] = i;
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
        if(!flag) break;
    }
    
    if(count == N) {
        printf("\nSafe sequence: ");
        for(i = 0; i < N; i++)
            printf("P%d ", seq[i]);
    } else {
        printf("\nSystem is not in safe state");
    }
    return 0;
} 