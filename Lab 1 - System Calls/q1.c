#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    // pid_t pid2 = fork();
    if(pid == 0) {
        printf("Child process ID: %d\n", getpid());
        printf("Child's Parent process ID: %d\n", getppid());

        printf("Child process is exiting...\n");
        exit(0);
    } else {
        printf("Parent process ID: %d\n", getpid());
        printf("Parent's Child process ID: %d\n", pid);
    }
}

pid_t = fork();
