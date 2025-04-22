#include <stdio.h>
#include <string.h>
/*
Overall summary:
Simple hierarchical directory implementation
Tree structure with directories and files

Algorithmic steps:
1. Create root directory
2. Add/remove items at any level
3. Show directory tree
*/

#define MAX 20

typedef struct {
    char name[20];
    int is_dir;
    int parent;
    int kids[MAX];
    int n_kids;
} Node;

int main() {
    Node tree[MAX];
    int n_nodes = 0;
    int curr = 0;  // Current directory
    
    // Setup root
    strcpy(tree[0].name, "root");
    tree[0].is_dir = 1;
    tree[0].parent = -1;
    tree[0].n_kids = 0;
    n_nodes++;
    
    while(1) {
        int choice;
        char name[20];
        
        printf("\nCurrent: %s", tree[curr].name);
        printf("\nOperations:");
        printf("\n1. Create Dir");
        printf("\n2. Create File");
        printf("\n3. Change Dir");
        printf("\n4. Delete");
        printf("\n5. Show Tree");
        printf("\n6. Exit");
        printf("\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
            case 2:
                if(tree[curr].n_kids < MAX) {
                    printf("Enter name: ");
                    scanf("%s", name);
                    // Check if exists
                    int exists = 0;
                    for(int i = 0; i < tree[curr].n_kids; i++)
                        if(strcmp(tree[tree[curr].kids[i]].name, name) == 0) {
                            exists = 1;
                            break;
                        }
                    if(!exists) {
                        strcpy(tree[n_nodes].name, name);
                        tree[n_nodes].is_dir = (choice == 1);
                        tree[n_nodes].parent = curr;
                        tree[n_nodes].n_kids = 0;
                        tree[curr].kids[tree[curr].n_kids++] = n_nodes++;
                    } else {
                        printf("Already exists\n");
                    }
                } else {
                    printf("Directory full\n");
                }
                break;
                
            case 3:
                printf("Enter path (.. for parent): ");
                scanf("%s", name);
                if(strcmp(name, "..") == 0) {
                    if(tree[curr].parent != -1)
                        curr = tree[curr].parent;
                    else
                        printf("At root\n");
                } else {
                    int found = 0;
                    for(int i = 0; i < tree[curr].n_kids; i++) {
                        int kid = tree[curr].kids[i];
                        if(strcmp(tree[kid].name, name) == 0 && tree[kid].is_dir) {
                            curr = kid;
                            found = 1;
                            break;
                        }
                    }
                    if(!found)
                        printf("Not found\n");
                }
                break;
                
            case 4:
                printf("Enter name: ");
                scanf("%s", name);
                int found = 0;
                for(int i = 0; i < tree[curr].n_kids; i++) {
                    if(strcmp(tree[tree[curr].kids[i]].name, name) == 0) {
                        // Move last kid here
                        if(i < tree[curr].n_kids - 1)
                            tree[curr].kids[i] = tree[curr].kids[tree[curr].n_kids-1];
                        tree[curr].n_kids--;
                        found = 1;
                        break;
                    }
                }
                if(!found)
                    printf("Not found\n");
                break;
                
            case 5:
                printf("\nDirectory Tree:\n");
                void show(Node t[], int node, int depth) {
                    for(int i = 0; i < depth; i++)
                        printf("  ");
                    printf("%s%s\n", t[node].is_dir ? "+" : "-", t[node].name);
                    if(t[node].is_dir)
                        for(int i = 0; i < t[node].n_kids; i++)
                            show(t, t[node].kids[i], depth + 1);
                }
                show(tree, 0, 0);
                break;
                
            case 6:
                return 0;
                
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
} 