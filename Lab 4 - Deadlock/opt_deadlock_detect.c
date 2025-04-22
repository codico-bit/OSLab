#include <stdio.h>
/*
Simple Deadlock Detection Algorithm:
1. Take input:
   - Number of processes (n) and resources (m)
   - Available resources (avail)
   - Currently allocated resources (alloc)
   - Process requests (req)
2. For each process:
   - If process can complete with available resources
     Mark it done and add its resources to available
   - Repeat until no more processes can complete
3. If any process remains unfinished, deadlock exists
4. Print deadlocked processes if any
*/

#define N 5  // processes
#define M 3  // resources

int main() {
    int i, j, k, flag;
    int alloc[N][M], req[N][M];
    int avail[M], work[M], finish[N];
    
    printf("Enter allocation matrix:\n");
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            scanf("%d", &alloc[i][j]);
            
    printf("Enter request matrix:\n");
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            scanf("%d", &req[i][j]);
            
    printf("Enter available resources:\n");
    for(i = 0; i < M; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }
    
    // Initialize finish array
    for(i = 0; i < N; i++)
        finish[i] = 0;
    
    // Find processes that can complete
    do {
        flag = 0;
        for(i = 0; i < N; i++) {
            if(!finish[i]) {
                for(j = 0; j < M; j++)
                    if(req[i][j] > work[j])
                        break;
                
                if(j == M) {
                    for(k = 0; k < M; k++)
                        work[k] += alloc[i][k];
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
    } while(flag);
    
    // Check for deadlock
    flag = 0;
    printf("\nDeadlocked processes: ");
    for(i = 0; i < N; i++) {
        if(!finish[i]) {
            printf("P%d ", i);
            flag = 1;
        }
    }
    if(!flag)
        printf("None (No deadlock)");
    return 0;
} 