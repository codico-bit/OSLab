#include <stdio.h>
#include <string.h>
/*
Overall summary:
Simple single-level directory implementation
Basic file operations in one directory

Algorithmic steps:
1. Create/delete files
2. Search files
3. Show directory contents
*/

#define MAX 20

int main() {
    char files[MAX][20];  // 20 chars per filename
    int n_files = 0;
    
    while(1) {
        int choice;
        char name[20];
        
        printf("\nDirectory Operations:");
        printf("\n1. Create File");
        printf("\n2. Delete File");
        printf("\n3. Search File");
        printf("\n4. Show Files");
        printf("\n5. Exit");
        printf("\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(n_files < MAX) {
                    printf("Enter name: ");
                    scanf("%s", name);
                    // Check if exists
                    int exists = 0;
                    for(int i = 0; i < n_files; i++)
                        if(strcmp(files[i], name) == 0) {
                            exists = 1;
                            break;
                        }
                    if(!exists)
                        strcpy(files[n_files++], name);
                    else
                        printf("File exists\n");
                } else {
                    printf("Directory full\n");
                }
                break;
                
            case 2:
                printf("Enter name: ");
                scanf("%s", name);
                int found = 0;
                for(int i = 0; i < n_files; i++)
                    if(strcmp(files[i], name) == 0) {
                        // Move last file to this position
                        if(i < n_files - 1)
                            strcpy(files[i], files[n_files-1]);
                        n_files--;
                        found = 1;
                        break;
                    }
                if(!found)
                    printf("File not found\n");
                break;
                
            case 3:
                printf("Enter name: ");
                scanf("%s", name);
                found = 0;
                for(int i = 0; i < n_files; i++)
                    if(strcmp(files[i], name) == 0) {
                        printf("Found at %d\n", i+1);
                        found = 1;
                        break;
                    }
                if(!found)
                    printf("File not found\n");
                break;
                
            case 4:
                if(n_files == 0)
                    printf("Empty directory\n");
                else {
                    printf("\nFiles:\n");
                    for(int i = 0; i < n_files; i++)
                        printf("%d. %s\n", i+1, files[i]);
                }
                break;
                
            case 5:
                return 0;
                
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
} 