#include <stdio.h>
/*
Overall summary:
Simple indexed file allocation
Files use index block to store block list

Algorithmic steps:
1. Get disk and file info
2. Allocate index and data blocks
3. Show allocation status
*/

#define MAX 20

int main() {
    int disk[MAX] = {0};     // 0=free, 1=used
    int index[MAX][MAX];     // Index blocks store block numbers
    char names[MAX][20];
    int idx_blocks[MAX];     // Index block for each file
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
        
        // Find free block for index
        int idx = -1;
        for(int j = 0; j < disk_size; j++)
            if(!disk[j]) {
                idx = j;
                break;
            }
        
        if(idx != -1) {
            idx_blocks[i] = idx;
            disk[idx] = 1;
            n_alloc++;
            
            // Find data blocks
            int found = 0;
            for(int j = 0; j < lengths[i]; j++) {
                int block = -1;
                for(int k = 0; k < disk_size; k++)
                    if(!disk[k]) {
                        block = k;
                        break;
                    }
                
                if(block != -1) {
                    index[idx][j] = block;
                    disk[block] = 1;
                    found++;
                } else {
                    printf("Not enough space\n");
                    break;
                }
            }
            
            if(found == lengths[i]) {
                n_alloc += lengths[i];
                // Show allocation
                printf("%s: [%d] -> ", names[i], idx);
                for(int j = 0; j < lengths[i]; j++)
                    printf("%d%s", index[idx][j], 
                           j < lengths[i]-1 ? "," : "");
                printf("\n");
            }
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