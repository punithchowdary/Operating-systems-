#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2;
    pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Failed to create first child process\n");
        return 1;
    } else if (pid1 == 0) {
        printf("First child process created with pid=%d\n", getpid());
        sleep(5);
        exit(0);
    } else {
        printf("First child process created with pid=%d\n", pid1);
    }
    pid2 = fork();

    if (pid2 < 0) {
        fprintf(stderr, "Failed to create second child process\n");
        return 1;
    } else if (pid2 == 0) {
        printf("Second child process created with pid=%d\n", getpid());
        sleep(10);
        exit(0);
    } else {
        printf("Second child process created with pid=%d\n", pid2);
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Both child processes completed\n");

    return 0;
}

