#include <stdio.h>
/*
Overall summary:
Simple linked file allocation
Files stored in linked blocks

Algorithmic steps:
Declare 5 arrays, 
1. Get disk and file info
2. Link free blocks
3. Show allocation status
*/

#define MAX 20

int main() {
    int disk[MAX] = {0};     // 0=free, 1=used
    int next[MAX];           // Next block in chain
    char names[MAX][20];
    int starts[MAX];         // Starting block of each file
    int lengths[MAX];
    int disk_size, n_files, n_alloc = 0;
    
    // Get input
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter number of files: ");
    scanf("%d", &n_files);
    
    // Allocate files
    for(int i = 0; i < n_files; i++) {
        printf("\nFile %d name: ", i+1);
        scanf("%s", names[i]);
        printf("Size (blocks): ");
        scanf("%d", &lengths[i]);
        
        // Find first free block
        int curr = -1;
        for(int j = 0; j < disk_size; j++)
            if(!disk[j]) {
                curr = j;
                break;
            }
        
        if(curr != -1) {
            starts[i] = curr;
            disk[curr] = 1;
            
            // Link blocks
            for(int j = 1; j < lengths[i]; j++) {
                int next_block = -1;
                for(int k = 0; k < disk_size; k++)
                    if(!disk[k]) {
                        next_block = k;
                        break;
                    }
                
                if(next_block != -1) {
                    next[curr] = next_block;
                    curr = next_block;
                    disk[curr] = 1;
                } else {
                    printf("Not enough space\n");
                    break;
                }
            }
            next[curr] = -1;  // End of chain
            n_alloc += lengths[i];
            
            // Show chain
            printf("%s: ", names[i]);
            curr = starts[i];
            printf("%d", curr);
            while(next[curr] != -1) {
                curr = next[curr];
                printf("->%d", curr);
            }
            printf("\n");
        } else {
            printf("%s: Not allocated\n", names[i]);
        }
    }
    
    printf("\nSummary:");
    printf("\nTotal blocks: %d", disk_size);
    printf("\nAllocated: %d", n_alloc);
    printf("\nFree: %d\n", disk_size - n_alloc);
    return 0;
} 