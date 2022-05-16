#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("child\n");
    } else {
        int wstatus;
        wait(&wstatus);

        printf("parent\n");
    }

    return EXIT_SUCCESS;
}
