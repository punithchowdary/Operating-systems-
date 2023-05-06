#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) {
        close(fd[0]);

        int data = 42;
        write(fd[1], &data, sizeof(data));

        close(fd[1]);
    }
    else {
        close(fd[1]);

        int data;
        read(fd[0], &data, sizeof(data));

        printf("Data received: %d\n", data);

        close(fd[0]);
    }

    return 0;
}

