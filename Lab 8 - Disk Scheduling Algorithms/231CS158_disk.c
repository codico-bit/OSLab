#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fcfs(int requests[], int n, int head) {
    int total_seek = 0;
    printf("\nFCFS Disk Scheduling:\n");
    printf("Head movement: %d", head);
    for (int i = 0; i < n; i++) {
        total_seek += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", total_seek);
}

void sstf(int requests[], int n, int head) {
    int total_seek = 0, completed[n];
    for (int i = 0; i < n; i++) completed[i] = 0;
    printf("\nSSTF Disk Scheduling:\n");
    printf("Head movement: %d", head);
    
    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX, min_index = -1;
        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(requests[j] - head) < min_seek) {
                min_seek = abs(requests[j] - head);
                min_index = j;
            }
        }
        total_seek += min_seek;
        head = requests[min_index];
        completed[min_index] = 1;
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", total_seek);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int total_seek = 0;
    printf("\nSCAN Disk Scheduling:\n");
    printf("Head movement: %d", head);
    int left[100], right[100], l = 0, r = 0;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) left[l++] = requests[i];
        else right[r++] = requests[i];
    }
    
    qsort(left, l, sizeof(int), (int (*)(const void*, const void*))abs);
    qsort(right, r, sizeof(int), (int (*)(const void*, const void*))abs);
    
    if (direction == 1) { 
        for (int i = 0; i < r; i++) {
            total_seek += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
        total_seek += abs(disk_size - 1 - head);
        head = disk_size - 1;
        printf(" -> %d", head);
        for (int i = l - 1; i >= 0; i--) {
            total_seek += abs(left[i] - head);
            head = left[i];
            printf(" -> %d", head);
        }
    } else { 
        for (int i = l - 1; i >= 0; i--) {
            total_seek += abs(left[i] - head);
            head = left[i];
            printf(" -> %d", head);
        }
        total_seek += abs(head - 0);
        head = 0;
        printf(" -> %d", head);
        for (int i = 0; i < r; i++) {
            total_seek += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
    }
}

int compare(const void * a,const void * b){
    return (*(int*)a - *(int*)b);
}

void SCAN(int a[], int head, int n, int size, char dir) {
    int tot = 0;
    qsort(a, n, sizeof(int), compare);
    printf("\nSeek sequence: ");
    if(dir == 'l'){
        if(head >= a[n - 1]) {
            for(int i=n-1; i>=0; i--){
                printf("%d -> ",a[i]);
            }
            tot += (head - a[0]);
        }
        else{
            for(int i=0; i<n; i++){
                printf("%d -> ",a[i]);
            }
            tot += (head + a[n - 1]);
        }
    }
    else if(dir == 'r'){
        if(head <= a[0]){
            for(int i=0; i<n; i++){
                printf("%d -> ",a[i]);
            }
            tot += (a[n - 1] - head);
        } 
        else{
            for(int i=n-1; i>=0; i--){
                printf("%d -> ",a[i]);
            }
            tot = (size - head + size - a[0]);
        }
    }
    printf("\nTotal seek time: %d\n", tot);
}

int main() {
    int n, head, disk_size, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);
    
    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size, direction);

    char dir;
    if(direction == 1){
        dir = 'r';
    }
    else{
        dir = 'l';
    }

    qsort(requests,n,sizeof(int),compare);
    SCAN(requests,head,n,disk_size,dir);
    
    return 0;
}