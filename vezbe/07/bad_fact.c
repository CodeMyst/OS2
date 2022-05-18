#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

void fact(int num) {
    // current iteration
    // this value will get smaller until it reaches 1
    int cur_num = num;

    // should we create a child process?
    int should_fork = 1;

    int pipe_input = -1;
    int pipe_output = -1;

    while (cur_num > 1 && should_fork) {
        int pfd[2];
        if (pipe(pfd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid > 0) {
            // parent

            // create a new file descriptor
            // pointing to the same pipe
            // done using dup because pfd descriptors
            // will be closed
            pipe_input = dup(pfd[0]);

            // we created a new child process
            // no need to fork anymore
            should_fork = 0;
        } else {
            // child

            // close the previously set pipe_output
            // only do this if this is the first
            // time we enter this part of the code
            if (pipe_output != -1) {
                close(pipe_output);
            }

            // get a new pipe_output
            pipe_output = dup(pfd[1]);

            // one step is done
            cur_num--;
        }

        close(pfd[0]);
        close(pfd[1]);
    }

    // print the current step
    printf("%d ", cur_num);

    unsigned long res = 1;

    // not the last child
    if (cur_num > 1) {
        // wait for the result from its child
        // and read it
        read(pipe_input, &res, sizeof(res));
        // we no longer need to read anymore
        close(pipe_input);

        // n (current number) * n-1 (child res)
        res *= cur_num;
    }

    // not the first (root)
    if (cur_num != num) {
        // write the result to the parent
        write(pipe_output, &res, sizeof(res));
        // we no longer need to write anymore
        close(pipe_output);
    }

    // the first (root)
    if (cur_num == num) {
        printf("res: %ld\n", res);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("at least one argument needed\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    int num = strtol(argv[1], NULL, 10);

    if (errno != 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (num < 0) {
        printf("can't calculate the factorial of negative numbers\n");
        exit(EXIT_FAILURE);
    }

    if (num == 0) {
        printf("res: 1\n");
        exit(EXIT_FAILURE);
    }

    fact(num);

    return EXIT_SUCCESS;
}