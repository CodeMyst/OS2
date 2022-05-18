#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void fib(int num) {
    int cur_num = num;
    int num_children = 0;

    int pipe_input[2];
    int pipe_output;

    int res = 0;

    while (cur_num > 1 && num_children < 2) {
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

        if (pid != 0) {
            pipe_input[num_children] = dup(pfd[0]);
            num_children++;
        } else {
            cur_num--;
            cur_num -= num_children;

            for (int i = 0; i < num_children - 1; i++) {
                close(pipe_input[i]);
            }

            num_children = 0;

            if (cur_num < num) {
                close(pipe_output);
            }

            pipe_output = dup(pfd[1]);
        }

        close(pfd[0]);
        close(pfd[1]);
    }

    if (cur_num <= 1) {
        res = cur_num;
    } else {
        int i;
        int tmp;
        res = 0;
        for (int i = 0; i < num_children; i++) {
            read(pipe_input[i], &tmp, sizeof(tmp));
            res += tmp;
            close (pipe_input[i]);
        }
    }

    if (cur_num == num) {
        printf("res: %d\n", res);
    } else {
        write(pipe_output, &res, sizeof(res));
        close(pipe_output);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("missing number argument\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    int num = strtol(argv[1], NULL, 10);

    if (errno != 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    fib(num);

    return EXIT_SUCCESS;
}
