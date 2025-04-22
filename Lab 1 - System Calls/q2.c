#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main() {
    int fp = open("/home/s1/Desktop/CS158/lab1/hello.txt", O_WRONLY | O_CREAT, 0644);
    if (fp == -1) {
        printf("error\n");
        return 1;
    }

    char *t = "swaraj";

    int w = write(fp, t, strlen(t));
    if (w == -1) {
        printf("error1\n");
        close(fp);
        return 1;
    }

    close(fp);

    fp = open("/home/s1/Desktop/CS158/lab1/hello.txt", O_RDONLY);
    if (fp == -1) {
        printf("error2\n");
        return 1;
    }

    char buff[256];
    int r = read(fp, buff, sizeof(buff));
    if (r == -1) {
        printf("error3\n");
        close(fp);
        return 1;
    }

    buff[r] = '\0';

    printf("%s\n", buff);

    close(fp);

    return 0;
}
