#include <stdio.h>
#include <string.h>
/*
Overall summary:
Simple two-level directory implementation
Users with their own files

Algorithmic steps:
1. Create users
2. Create files in user dirs
3. Show directory tree
*/

#define MAX 20

int main() {
    char users[MAX][20];  // 20 chars per name
    char files[MAX][MAX][20];  // MAX files per user
    int n_users = 0;
    int n_files[MAX] = {0};  // Files per user
    
    while(1) {
        int choice;
        char uname[20], fname[20];
        
        printf("\nDirectory Operations:");
        printf("\n1. Create User");
        printf("\n2. Create File");
        printf("\n3. Delete File");
        printf("\n4. Search File");
        printf("\n5. Show All");
        printf("\n6. Exit");
        printf("\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(n_users < MAX) {
                    printf("Enter username: ");
                    scanf("%s", uname);
                    // Check if exists
                    int exists = 0;
                    for(int i = 0; i < n_users; i++)
                        if(strcmp(users[i], uname) == 0) {
                            exists = 1;
                            break;
                        }
                    if(!exists)
                        strcpy(users[n_users++], uname);
                    else
                        printf("User exists\n");
                } else {
                    printf("Max users reached\n");
                }
                break;
                
            case 2:
                printf("Enter username: ");
                scanf("%s", uname);
                // Find user
                int uid = -1;
                for(int i = 0; i < n_users; i++)
                    if(strcmp(users[i], uname) == 0) {
                        uid = i;
                        break;
                    }
                if(uid == -1) {
                    printf("User not found\n");
                    break;
                }
                if(n_files[uid] < MAX) {
                    printf("Enter filename: ");
                    scanf("%s", fname);
                    strcpy(files[uid][n_files[uid]++], fname);
                } else {
                    printf("Directory full\n");
                }
                break;
                
            case 3:
                printf("Enter user and file: ");
                scanf("%s %s", uname, fname);
                uid = -1;
                for(int i = 0; i < n_users; i++)
                    if(strcmp(users[i], uname) == 0) {
                        uid = i;
                        break;
                    }
                if(uid == -1) {
                    printf("User not found\n");
                    break;
                }
                int found = 0;
                for(int i = 0; i < n_files[uid]; i++)
                    if(strcmp(files[uid][i], fname) == 0) {
                        // Move last file here
                        if(i < n_files[uid] - 1)
                            strcpy(files[uid][i], files[uid][n_files[uid]-1]);
                        n_files[uid]--;
                        found = 1;
                        break;
                    }
                if(!found)
                    printf("File not found\n");
                break;
                
            case 4:
                printf("Enter user and file: ");
                scanf("%s %s", uname, fname);
                found = 0;
                for(int i = 0; i < n_users; i++)
                    if(strcmp(users[i], uname) == 0)
                        for(int j = 0; j < n_files[i]; j++)
                            if(strcmp(files[i][j], fname) == 0) {
                                printf("Found in %s's dir\n", uname);
                                found = 1;
                                break;
                            }
                if(!found)
                    printf("File not found\n");
                break;
                
            case 5:
                if(n_users == 0)
                    printf("No users\n");
                else {
                    printf("\nDirectory Tree:\n");
                    for(int i = 0; i < n_users; i++) {
                        printf("\n%s/\n", users[i]);
                        if(n_files[i] == 0)
                            printf("  Empty\n");
                        else
                            for(int j = 0; j < n_files[i]; j++)
                                printf("  %s\n", files[i][j]);
                    }
                }
                break;
                
            case 6:
                return 0;
                
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
} 