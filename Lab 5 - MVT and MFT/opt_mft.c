#include <stdio.h>
/*
Simple MFT (Multiprogramming with Fixed Tasks):
1. Take:
   - Total memory size
   - Block size (fixed partition size)
   - Number of processes
2. Calculate:
   - Number of blocks = memory size / block size
   - Internal fragmentation for each process
3. For each process:
   - If process fits in block, allocate it
   - Track internal fragmentation
4. Print allocation and fragmentation details
*/

int main() {
    int ms, bs, nob, n, i;
    int p[10];     // process sizes
    int frag[10];  // internal fragmentation
    
    printf("Enter memory size: ");
    scanf("%d", &ms);
    printf("Enter block size: ");
    scanf("%d", &bs);
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    nob = ms/bs;  // number of blocks
    printf("\nNumber of blocks: %d", nob);
    
    printf("\nEnter process sizes:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &p[i]);
    }
    
    printf("\nProcess\tSize\tBlock\tFragment");
    for(i = 0; i < n && i < nob; i++) {
        if(p[i] <= bs) {
            frag[i] = bs - p[i];
            printf("\nP%d\t%d\t%d\t%d", i+1, p[i], i+1, frag[i]);
        } else {
            printf("\nP%d\t%d\tToo big", i+1, p[i]);
        }
    }
    
    if(i < n)
        printf("\nRemaining processes cannot be allocated");
    return 0;
} 