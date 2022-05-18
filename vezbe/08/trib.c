#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * Calculating the tribonacci series in a bad way
 *
 * Trib(1) = 1
 * Trib(2) = 1
 * Trib(3) = 2
 * Trib(x) = Trib(x-1) + Trib(x-2) + Trib(x-3)
 *
 * For every step, 3 child processes are created
 */

// number of needed children processes for each process
// for each step we have to calculate t(x-1), t(x-2) and t(x-3)
// 3 processes will get created for each of those steps
const int needed_children = 3;

void trib(int num) {
    // keep track of the current number to calculate
    int cur_num = num;

    // current number of created child processes
    int num_children = 0;

    // need a pipe input for each child
    // the result needs to be read from all three children
    int pipe_inputs[needed_children];
    // but we need to write to only one parent
    int pipe_output = -1;

    // until the end is reached
    // and the current number of children is not enough
    while (cur_num > 1 && num_children < needed_children) {
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

            // create a new pipe descriptor for this process
            // pointing to the same pipe
            // done using dup because pfd descriptors
            // will be closed
            pipe_inputs[num_children] = dup(pfd[0]);

            num_children++;
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

            // ????
            cur_num -= num_children + 1;

            // we only need the pipe for this child
            // and not the others
            for (int i = 0; i < num_children - 1; i++) {
                close(pipe_inputs[i]);
            }

            // reset the children count for this process
            num_children = 0;
        }

        close(pfd[0]);
        close(pfd[1]);
    }

    unsigned long res = 0;

    // for Trib(1) and Trib(2) = 1
    // and for Trib(3) = 2
    // set that as the result (trivial cases)
    if (cur_num <= 2) {
        res = 1;
    } else if (cur_num == 3) {
        res = 2;
    } else {
        // for each of the children, read their result
        // and add it to the current result
        int tmp;
        for (int i = 0; i < num_children; i++) {
            read(pipe_inputs[i], &tmp, sizeof(tmp));
            res += tmp;
            close(pipe_inputs[i]);
        }
    }

    // if this is the first one (root)
    if (cur_num == num) {
        printf("res: %ld\n", res);
    } else {
        // if not the first one
        // write the result back to the parent
        write(pipe_output, &res, sizeof(res));
        close(pipe_output);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("one argument required.\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    int num = strtol(argv[1], NULL, 10);
    if (errno != 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    trib(num);

    return EXIT_SUCCESS;
}