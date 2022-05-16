#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void fact(int num) {
    int cur_num = num;
    int should_fork = 1;

    int pipe_input;
    int pipe_output;

    while (cur_num > 1 && should_fork) {
        int pfd[2];
        if (pipe(pfd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid > 0) {
            pipe_input = dup(pfd[0]);
            should_fork = 0;
        } else {
            if (cur_num < num) {
                close(pipe_output);
            }

            pipe_output = dup(pfd[1]);

            cur_num--;
        }

        close(pfd[0]);
        close(pfd[1]);
    }

    printf("%d ", cur_num);

    unsigned long res = 1;

    if (cur_num > 1) {
        read(pipe_input, &res, sizeof(res));
        close(pipe_input);
        res *= cur_num;
    }

    if (cur_num < num) {
        write(pipe_output, &res, sizeof(res));
        close(pipe_output);
    }

    if (cur_num == num) {
        printf("res: %lu\n", res);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("needs at least 2 args\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    int num = strtol(argv[1], NULL, 10);
    if (errno != 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (num < 0) {
        printf("can't calc fact of negative nums\n");
        exit(EXIT_FAILURE);
    }

    if (num == 0) {
        printf("res: 0\n");
        exit(EXIT_SUCCESS);
    }

    fact(num);

    return EXIT_SUCCESS;
}
