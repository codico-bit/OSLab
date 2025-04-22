#include <stdio.h>
#include <stdlib.h>
/*
Overall summary:
Simple FCFS disk scheduling implementation
Process requests in order of arrival

Algorithmic steps:
1. Get head position and requests
2. Process in arrival order
3. Show total head movement
*/

#define MAX 50

int main() {
    int requests[MAX];
    int n_requests, head, total = 0;
    
    // Get input
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter number of requests: ");
    scanf("%d", &n_requests);
    printf("Enter request queue: ");
    for(int i = 0; i < n_requests; i++)
        scanf("%d", &requests[i]);
    
    // Process requests in FCFS order
    printf("\nHead movement:\n");
    printf("%d", head);
    for(int i = 0; i < n_requests; i++) {
        total += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    
    printf("\nTotal head movement: %d", total);
    printf("\nAverage head movement: %.2f\n", (float)total/n_requests);
    return 0;
} 