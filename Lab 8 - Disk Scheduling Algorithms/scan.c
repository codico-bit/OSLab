#include <stdio.h>
#include <stdlib.h>
/*
Overall summary:
Implement SCAN (Elevator) disk scheduling algorithm
Move disk head in one direction until end, then reverse

Algorithmic steps:
1. Get disk range, request queue, head position and direction
2. Sort requests for efficient processing
3. Based on direction:
   - Move head towards end, serving requests
   - Reach end of disk
   - Move back, serving remaining requests
4. Calculate and display total seek time

In main,
- Take input for disk parameters and requests
- Sort requests in ascending order
- Process requests based on direction
- Track and display seek operations
*/

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int max_disk_range, queue_size, i, head, seek_time = 0, direction;
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

    printf("Enter the direction of the head (1 for right, 0 for left): ");
    scanf("%d", &direction);

    // Sort requests for efficient processing
    qsort(queue, queue_size, sizeof(int), compare);

    printf("\nHead movement:\n");
    if (direction == 0) {
        // Moving left first
        printf("Moving left:\n");
        for (i = queue_size - 1; i >= 0; i--) {
            if (queue[i] < head) {
                printf("%d -> %d\n", head, queue[i]);
                seek_time += abs(queue[i] - head);
                head = queue[i];
            }
        }
        // Go to start of disk
        printf("%d -> 0\n", head);
        seek_time += abs(head);
        head = 0;
        
        // Now move right
        printf("Moving right:\n");
        for (i = 0; i < queue_size; i++) {
            if (queue[i] > head) {
                printf("%d -> %d\n", head, queue[i]);
                seek_time += abs(queue[i] - head);
                head = queue[i];
            }
        }
    } else {
        // Moving right first
        printf("Moving right:\n");
        for (i = 0; i < queue_size; i++) {
            if (queue[i] > head) {
                printf("%d -> %d\n", head, queue[i]);
                seek_time += abs(queue[i] - head);
                head = queue[i];
            }
        }
        // Go to end of disk
        printf("%d -> %d\n", head, max_disk_range);
        seek_time += abs(max_disk_range - head);
        head = max_disk_range;
        
        // Now move left
        printf("Moving left:\n");
        for (i = queue_size - 1; i >= 0; i--) {
            if (queue[i] < head) {
                printf("%d -> %d\n", head, queue[i]);
                seek_time += abs(queue[i] - head);
                head = queue[i];
            }
        }
    }

    // Display statistics
    printf("\nTotal seek time: %d", seek_time);
    printf("\nAverage seek time: %.2f\n", (float)seek_time / queue_size);

    free(queue);
    return 0;
}
