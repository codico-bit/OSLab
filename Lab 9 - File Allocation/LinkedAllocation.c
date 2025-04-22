// Linked Allocation
#include <stdio.h>
#include <stdlib.h>
#define DISK_SIZE 10

typedef struct BlockNode {
    int diskBlock;
    struct BlockNode *next;
} BlockNode;

BlockNode *allocateLinked(int diskStatus[], int fileBlockCount,int *fileBlockSequence) {
    if (fileBlockCount <= 0) return NULL;

    BlockNode *head = NULL, *temp = NULL;
    int allocatedCount = 0;
    int index = 0;

    for (int i = 0; i < DISK_SIZE && allocatedCount < fileBlockCount; i++) {
        if (diskStatus[i] == 0) { // If block is free
            BlockNode *newNode = (BlockNode *)malloc(sizeof(BlockNode));

            if (!newNode) return NULL;
            newNode->diskBlock = i;
            newNode->next = NULL;
            *(fileBlockSequence + index) = i;
            index++;

            diskStatus[i] = 1; // Mark as allocated
            if (!head) head = newNode;
            else temp->next = newNode;
            temp = newNode;
            allocatedCount++;
        }
    }
    if (allocatedCount < fileBlockCount) {
        printf("Allocation failed: Not enough free blocks available.\n");
        return NULL;
    }
    return head;
}

int main() {
    int fileBlockCount;
    printf("Enter number of file blocks: ");
    scanf("%d", &fileBlockCount);

    if (fileBlockCount <= 0) {
        printf("Allocation failed: Invalid block size.\n");
        return 0;
    }

    int diskStatus[DISK_SIZE];
    printf("Enter disk status (0 for free, 1 for occupied, space-separated): ");
    for (int i = 0; i < DISK_SIZE; i++) {
        scanf("%d", &diskStatus[i]);
    }

    int fileBlockSequence[fileBlockCount];

    BlockNode *file = allocateLinked(diskStatus, fileBlockCount,fileBlockSequence);
    if (file){
        printf("File allocated successfully using Linked Allocation.\n");
        for(int i=0;i<fileBlockCount;i++){
            printf("%d->",fileBlockSequence[i]);
        }
        printf("END");
    }
    else
        printf("Allocation failed: Not enough free blocks available.\n");
    return 0;
}