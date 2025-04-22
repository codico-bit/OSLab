#include <stdio.h>
#include <stdlib.h>
/*
Overall summary:
Simple SCAN disk scheduling implementation
Process requests in elevator style

Algorithmic steps:
1. Get head position and requests
2. Sort requests
3. Process in one direction then reverse
*/

#define MAX 50

int main() {
    int requests[MAX], sorted[MAX];
    int n_requests, head, total = 0;
    int direction;  // 1 for right, 0 for left
    
    // Get input
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter number of requests: ");
    scanf("%d", &n_requests);
    printf("Enter request queue: ");
    for(int i = 0; i < n_requests; i++) {
        scanf("%d", &requests[i]);
        sorted[i] = requests[i];
    }
    printf("Enter direction (0=left, 1=right): ");
    scanf("%d", &direction);
    
    // Sort requests
    for(int i = 0; i < n_requests-1; i++)
        for(int j = 0; j < n_requests-i-1; j++)
            if(sorted[j] > sorted[j+1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
    
    // Find position where head lies
    int pos;
    for(pos = 0; pos < n_requests && sorted[pos] < head; pos++);
    
    // Process requests in SCAN order
    printf("\nHead movement:\n");
    printf("%d", head);
    
    if(direction) {  // Moving right
        for(int i = pos; i < n_requests; i++) {
            total += abs(sorted[i] - head);
            head = sorted[i];
            printf(" -> %d", head);
        }
        for(int i = pos-1; i >= 0; i--) {
            total += abs(sorted[i] - head);
            head = sorted[i];
            printf(" -> %d", head);
        }
    } else {  // Moving left
        for(int i = pos-1; i >= 0; i--) {
            total += abs(sorted[i] - head);
            head = sorted[i];
            printf(" -> %d", head);
        }
        for(int i = pos; i < n_requests; i++) {
            total += abs(sorted[i] - head);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }
    
    printf("\nTotal head movement: %d", total);
    printf("\nAverage head movement: %.2f\n", (float)total/n_requests);
    return 0;
} 