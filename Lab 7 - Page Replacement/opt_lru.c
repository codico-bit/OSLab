#include <stdio.h>
/*
Overall summary:
Simple LRU page replacement implementation
Replace least recently used page when frame is full

Algorithmic steps:
1. Get frames and pages
2. Track page usage time
3. Replace oldest used page
*/

#define MAX 20

int main() {
    int frames[MAX], pages[MAX], time[MAX];
    int n_frames, n_pages, page_faults = 0;
    
    // Get input
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);
    printf("Enter number of pages: ");
    scanf("%d", &n_pages);
    printf("Enter reference string: ");
    for(int i = 0; i < n_pages; i++)
        scanf("%d", &pages[i]);
    
    // Initialize frames and time
    for(int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        time[i] = 0;
    }
    
    // Process each page
    printf("\nPage Replacement Process:\n");
    for(int i = 0; i < n_pages; i++) {
        int found = 0;
        
        // Check if page exists
        for(int j = 0; j < n_frames; j++) {
            if(frames[j] == pages[i]) {
                time[j] = i + 1;  // Update access time
                found = 1;
                break;
            }
        }
        
        // If page not found
        if(!found) {
            // Find LRU position
            int lru = 0;
            for(int j = 1; j < n_frames; j++)
                if(time[j] < time[lru])
                    lru = j;
            
            frames[lru] = pages[i];
            time[lru] = i + 1;
            page_faults++;
            
            // Show current frames
            printf("Page %d -> [", pages[i]);
            for(int j = 0; j < n_frames; j++)
                printf("%2d%s", frames[j], j < n_frames-1 ? "," : "");
            printf(" ] Fault\n");
        }
    }
    
    printf("\nTotal page faults: %d", page_faults);
    printf("\nPage fault rate: %.2f%%\n", (float)page_faults/n_pages * 100);
    return 0;
} 