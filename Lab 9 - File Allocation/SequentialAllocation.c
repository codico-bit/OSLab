// Sequential Allocation
#include <stdio.h>
#include <stdbool.h>
#define DISK_SIZE 10

/*
Overall summary:
take user input for disk size, then take those many 0s and 1s as input to know whether disk index is free or not
then enter number of file blocks required, and run the sequential allocaiton
in sequantial allocaiton, iterate through iterate through i -> i+j (j goes from 0 to fileblocks)
basically we check if continuously fileblocks space is free
if not, set bool freespace to false and break;
if it stays true, then set those (i -> i+j) to 1 and return true;

*/

bool allocateSequential(int diskBlocks[], int fileBlocks) {
    for (int i = 0; i <= DISK_SIZE - fileBlocks; i++) {
        bool freeSpace = true;
        for (int j = 0; j < fileBlocks; j++) {
            if (diskBlocks[i + j] == 1) { // 1 means occupied
                freeSpace = false;
                break;
            }
        }
        if (freeSpace) {
            for (int j = 0; j < fileBlocks; j++) {
                diskBlocks[i + j] = 1;
            }
            return true;
        }
    }
    return false;
}

int main() {
    int diskBlocks[DISK_SIZE];
    int fileBlocks;
    printf("Enter disk status (0 for free, 1 for occupied, space-separated): ");
    for (int i = 0; i < DISK_SIZE; i++) {
        scanf("%d", &diskBlocks[i]);
    }
    printf("Enter number of file blocks: ");
    scanf("%d", &fileBlocks);
    if (allocateSequential(diskBlocks, fileBlocks))
        printf("File allocated successfully using Sequential Allocation.\n");
    else
        printf("Allocation failed: Not enough contiguous space.\n");
    return 0;
}