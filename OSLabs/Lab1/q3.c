#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *s = (char *)malloc(1024);
    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    strcpy(s, "Hello world");
    printf("String in allocated memory: %s\n", s);

    void *new_break = s + 2048;
    if (brk(new_break) == -1) {
        printf("Failed to increase the data segment size using brk().\n");
        free(s);
        return 1;
    }

    printf("Heap size increased.\n");

    new_break = s + 1024;
    if (brk(new_break) == -1) {
        printf("Failed to decrease the data segment size using brk().\n");
        free(s);
        return 1;
    }

    printf("Heap size decreased.\n");

    free(s);

    return 0;
}
