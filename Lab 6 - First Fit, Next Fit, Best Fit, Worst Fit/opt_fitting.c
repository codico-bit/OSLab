#include <stdio.h>
#include <limits.h>
/*
Overall summary:
Simple implementation of memory allocation algorithms
First Fit, Best Fit, Worst Fit, Next Fit in one program

Algorithmic steps:
1. Get blocks and processes
2. Run each algorithm on copy of blocks
3. Show allocation results
*/

#define MAX 10

int main() {
    int blocks[MAX], processes[MAX];
    int n_blocks, n_processes;
    
    // Get input
    printf("Enter number of blocks: ");
    scanf("%d", &n_blocks);
    printf("Enter block sizes: ");
    for(int i = 0; i < n_blocks; i++)
        scanf("%d", &blocks[i]);
    printf("Enter number of processes: ");
    scanf("%d", &n_processes);
    printf("Enter process sizes: ");
    for(int i = 0; i < n_processes; i++)
        scanf("%d", &processes[i]);
    
    // Make copies for each algorithm
    int ff[MAX], bf[MAX], wf[MAX], nf[MAX];
    for(int i = 0; i < n_blocks; i++)
        ff[i] = bf[i] = wf[i] = nf[i] = blocks[i];
    
    // First Fit
    printf("\nFirst Fit:\n");
    for(int i = 0; i < n_processes; i++) {
        int allocated = 0;
        for(int j = 0; j < n_blocks; j++) {
            if(ff[j] >= processes[i]) {
                printf("Process %d (%d KB) -> Block %d (%d KB)\n", 
                       i+1, processes[i], j+1, ff[j]);
                ff[j] -= processes[i];
                allocated = 1;
                break;
            }
        }
        if(!allocated)
            printf("Process %d (%d KB) -> Not Allocated\n", i+1, processes[i]);
    }
    
    // Best Fit
    printf("\nBest Fit:\n");
    for(int i = 0; i < n_processes; i++) {
        int best_idx = -1, min_diff = INT_MAX;
        for(int j = 0; j < n_blocks; j++) {
            if(bf[j] >= processes[i] && bf[j] - processes[i] < min_diff) {
                min_diff = bf[j] - processes[i];
                best_idx = j;
            }
        }
        if(best_idx != -1) {
            printf("Process %d (%d KB) -> Block %d (%d KB)\n", 
                   i+1, processes[i], best_idx+1, bf[best_idx]);
            bf[best_idx] -= processes[i];
        } else {
            printf("Process %d (%d KB) -> Not Allocated\n", i+1, processes[i]);
        }
    }
    
    // Worst Fit
    printf("\nWorst Fit:\n");
    for(int i = 0; i < n_processes; i++) {
        int worst_idx = -1, max_diff = -1;
        for(int j = 0; j < n_blocks; j++) {
            if(wf[j] >= processes[i] && wf[j] - processes[i] > max_diff) {
                max_diff = wf[j] - processes[i];
                worst_idx = j;
            }
        }
        if(worst_idx != -1) {
            printf("Process %d (%d KB) -> Block %d (%d KB)\n", 
                   i+1, processes[i], worst_idx+1, wf[worst_idx]);
            wf[worst_idx] -= processes[i];
        } else {
            printf("Process %d (%d KB) -> Not Allocated\n", i+1, processes[i]);
        }
    }
    
    // Next Fit
    printf("\nNext Fit:\n");
    int last = 0;
    for(int i = 0; i < n_processes; i++) {
        int allocated = 0;
        int j = last;
        do {
            if(nf[j] >= processes[i]) {
                printf("Process %d (%d KB) -> Block %d (%d KB)\n", 
                       i+1, processes[i], j+1, nf[j]);
                nf[j] -= processes[i];
                last = j;
                allocated = 1;
                break;
            }
            j = (j + 1) % n_blocks;
        } while(j != last);
        
        if(!allocated)
            printf("Process %d (%d KB) -> Not Allocated\n", i+1, processes[i]);
    }
    
    return 0;
} 