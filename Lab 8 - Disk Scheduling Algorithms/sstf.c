#include <stdio.h>
#include <stdlib.h>
/*
Overall summary:
Implement SSTF (Shortest Seek Time First) disk scheduling
Choose request with minimum seek time from current position

Algorithmic steps:
1. Get disk requests and initial head position
2. For each request to be served:
   - Find unserved request with minimum seek time
   - Move head to that request's position
   - Mark request as served
3. Calculate and display total seek operations

In main,
- Initialize request queue and head position
- Process requests using SSTF algorithm
- Track and display seek operations
*/

void SSTF(int requests[], int n, int initial_position) {
    int total_seek_count = 0;
    int current_position = initial_position;
    int visited[n];
    
    // Initialize visited array
    for (int i = 0; i < n; i++) 
        visited[i] = 0;

    printf("\nHead movement:\n");
    // Process all requests
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int index = -1;
        
        // Find closest unserved request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - current_position);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }
        
        visited[index] = 1;
        total_seek_count += min_distance;
        printf("%d -> %d (Seek: %d)\n", current_position, requests[index], min_distance);
        current_position = requests[index];
    }

    // Display statistics
    printf("\nTotal seek operations: %d\n", total_seek_count);
    printf("Average seek length: %.2f\n", (float)total_seek_count / n);
}

int main() {
    int requests[] = {92, 100, 40, 148, 67, 170, 29, 10};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_position = 45;
    
    printf("SSTF Disk Scheduling\n");
    printf("Initial head position: %d\n", initial_position);
    printf("Request queue: ");
    for(int i = 0; i < n; i++)
        printf("%d ", requests[i]);
    printf("\n");
    
    SSTF(requests, n, initial_position);
    return 0;
}
