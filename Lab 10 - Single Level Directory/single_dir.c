#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 100
/*
Summary
strcmp returns 0 if strings are equal, and 1 or -1 depending on the lexicographic order of the strings, 1 if the first string is greater than the second, -1 if the first string is less than the second
Create four functions: for creating, deleting, search and display files.
in create file, check for MAX_FILE first
- use scanf %s to take file input in new var called filename[array\]
use strcmp with filename to check if file already exists
then copy filename array via strcpy to directory[fileCount]
increment fileCount
print success message

in delete file, check for fileCount first if directory is empty
- use scanf %s to take file input in new var called filename[array\]
use strcmp with filename to check if file already exists
if found, shift all files after the index to the left
decrement fileCount
print success message

in search file, check for fileCount first
- use scanf %s to take file input in new var called filename[array\]
use strcmp with filename to check if file already exists    
*/
char directory[MAX_FILES][MAX_FILENAME_LENGTH];
int fileCount = 0;

void createFile() {
    if (fileCount >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name to create: ");
    scanf("%s", filename);


    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i], filename) == 0) {
        printf("File '%s' already exists.\n", filename); // check if it already exists
        return;
        }
    }

    strcpy(directory[fileCount], filename);
    fileCount++;
    printf("File '%s' created successfully.\n", filename);
}

void deleteFile() {
    if (fileCount == 0) {
        printf("Directory is empty. Nothing to delete.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    int found = 0;
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i], filename) == 0) {
            found = 1;
            // Shift the remaining files
            for (int j = i; j < fileCount - 1; j++) {
                strcpy(directory[j], directory[j + 1]);
            }
            fileCount--;
            printf("File '%s' deleted successfully.\n", filename);
            break;
        }
    }

    if (!found) {
        printf("File '%s' not found.\n", filename);
    }
}

void searchFile() {
    if (fileCount == 0) {
        printf("Directory is empty.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name to search: ");
    scanf("%s", filename);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i], filename) == 0) {
            printf("File '%s' found in the directory.\n", filename);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}

void displayFiles() {
    if (fileCount == 0) {
        printf("No files in the directory.\n");
        return;
    }

    printf("Files in the directory:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s\n", directory[i]);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nSingle Level Directory Simulation\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}