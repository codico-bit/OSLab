#include <stdio.h>
#include <stdlib.h>
/*
Overall summary:
Implement FCFS (First Come First Serve) disk scheduling
Process disk requests in the order they arrive

Algorithmic steps:
1. Get disk range, request queue, and initial head position
2. For each request in queue:
   - Calculate seek time as absolute difference from current head
   - Move head to new position
3. Calculate and display total and average seek time

In main,
- Take input for disk range and queue size
- Get request queue and initial head position
- Process requests in FCFS order
- Display seek time statistics
*/

int main() {
    int max_disk_range, queue_size, i, head, seek_time = 0;
    int *queue;

    // Get disk parameters
    printf("Enter the max range of disk: ");
    scanf("%d", &max_disk_range);

    printf("Enter the size of queue request: ");
    scanf("%d", &queue_size);

    // Get request queue
    queue = (int *)malloc(queue_size * sizeof(int));
    printf("Enter the queue of disk positions to be read: ");
    for (i = 0; i < queue_size; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Process requests in FCFS order
    printf("\nHead movement:\n");
    for (i = 0; i < queue_size; i++) {
        printf("%d -> %d\n", head, queue[i]);
        seek_time += abs(queue[i] - head);
        head = queue[i];
    }

    // Display statistics
    printf("\nTotal seek time: %d", seek_time);
    printf("\nAverage seek time: %.2f\n", (float)seek_time / queue_size);

    free(queue);
    return 0;
}
