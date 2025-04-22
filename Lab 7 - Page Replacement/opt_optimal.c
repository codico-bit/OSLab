#include <stdio.h>
/*
Overall summary:
Simple Optimal page replacement implementation
Replace page that won't be used for longest time

Algorithmic steps:
1. Get frames and pages
2. Find future use of each page
3. Replace page used farthest in future
*/

#define MAX 20

int main() {
    int frames[MAX], pages[MAX];
    int n_frames, n_pages, page_faults = 0;
    
    // Get input
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);
    printf("Enter number of pages: ");
    scanf("%d", &n_pages);
    printf("Enter reference string: ");
    for(int i = 0; i < n_pages; i++)
        scanf("%d", &pages[i]);
    
    // Initialize frames
    for(int i = 0; i < n_frames; i++)
        frames[i] = -1;
    
    // Process each page
    printf("\nPage Replacement Process:\n");
    for(int i = 0; i < n_pages; i++) {
        int found = 0;
        
        // Check if page exists
        for(int j = 0; j < n_frames; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        
        // If page not found
        if(!found) {
            // Find page to replace
            int pos = 0;
            if(frames[0] != -1) {
                int farthest = -1;
                for(int j = 0; j < n_frames; j++) {
                    int k;
                    for(k = i + 1; k < n_pages; k++) {
                        if(frames[j] == pages[k]) break;
                    }
                    if(k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }
            
            frames[pos] = pages[i];
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