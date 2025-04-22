#include <stdio.h>
/*
Overall summary:
Simple sequential file allocation
Files stored in contiguous blocks

Algorithmic steps:
1. Get disk and file info
2. Find contiguous space
3. Show allocation status
*/

#define MAX 20

int main() {
    int disk[MAX] = {0};  // 0=free, 1=used
    char names[MAX][20];
    int starts[MAX], lengths[MAX];
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
        
        // Find contiguous space
        int found = 0;
        for(int j = 0; j <= disk_size - lengths[i]; j++) {
            int free = 1;
            for(int k = 0; k < lengths[i] && free; k++)
                if(disk[j+k]) free = 0;
            
            if(free) {
                starts[i] = j;
                for(int k = 0; k < lengths[i]; k++)
                    disk[j+k] = 1;
                found = 1;
                n_alloc += lengths[i];
                break;
            }
        }
        
        // Show allocation
        printf("%s: ", names[i]);
        if(found)
            printf("Blocks %d to %d\n", starts[i], starts[i] + lengths[i] - 1);
        else
            printf("Not allocated\n");
    }
    
    // Count fragments
    int fragments = 0, curr_free = 0;
    for(int i = 0; i < disk_size; i++) {
        if(!disk[i]) curr_free++;
        else if(curr_free > 0) {
            if(curr_free < lengths[n_files-1])
                fragments += curr_free;
            curr_free = 0;
        }
    }
    if(curr_free > 0 && curr_free < lengths[n_files-1])
        fragments += curr_free;
    
    printf("\nSummary:");
    printf("\nTotal blocks: %d", disk_size);
    printf("\nAllocated: %d", n_alloc);
    printf("\nFree: %d", disk_size - n_alloc);
    printf("\nFragments: %d\n", fragments);
    return 0;
} 