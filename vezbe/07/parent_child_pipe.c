#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int pipefd[2];
    int piper = pipe(pipefd);

    if (piper == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[0]); // close read end

        printf("child\n");

        char* msg = "hello from child";
        write(pipefd[1], msg, strlen(msg));
    } else {
        close(pipefd[1]); // close write end

        char msg[250];
        read(pipefd[0], msg, 250);

        printf("message from child: %s\n", msg);

        int wstatus;
        wait(&wstatus);

        printf("parent\n");
    }

    return EXIT_SUCCESS;
}
