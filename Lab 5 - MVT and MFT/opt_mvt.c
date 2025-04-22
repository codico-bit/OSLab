#include <stdio.h>
/*
Simple MVT (Multiprogramming with Variable Tasks):
1. Take total memory size
2. For each process:
   - Take memory requirement
   - If memory available, allocate it
   - If not enough memory, stop
3. Track:
   - Memory allocated to each process
   - Total memory allocated
   - External fragmentation
*/

int main() {
    int ms, n = 0, i;
    int p[10];  // process sizes
    int free;   // free memory
    char c = 'y';
    
    printf("Enter memory size: ");
    scanf("%d", &ms);
    free = ms;
    
    for(i = 0; c == 'y'; i++, n++) {
        printf("Enter P%d size: ", i+1);
        scanf("%d", &p[i]);
        
        if(p[i] <= free) {
            printf("Allocated P%d\n", i+1);
            free -= p[i];
        } else {
            printf("Memory full\n");
            break;
        }
        
        printf("Continue? (y/n): ");
        scanf(" %c", &c);
    }
    
    printf("\nTotal memory: %d", ms);
    printf("\nProcess\tSize");
    for(i = 0; i < n; i++)
        printf("\nP%d\t%d", i+1, p[i]);
    printf("\nAllocated: %d", ms-free);
    printf("\nExternal Fragmentation: %d", free);
    return 0;
} 