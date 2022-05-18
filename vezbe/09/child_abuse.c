#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int child_working = 0;

void child_work(int sig) {
    child_working = 1;
}

void child_sleep(int sig) {
    child_working = 0;
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        struct sigaction act1;
        act1.sa_handler = &child_work;
        sigaction(SIGUSR1, &act1, NULL);

        struct sigaction act2;
        act2.sa_handler = &child_sleep;
        sigaction(SIGUSR2, &act2, NULL);

        while (1) {
            if (child_working) {
                printf("working\n");
            } else {
                printf("sleeping\n");
            }

            sleep(1);
        }
    } else {
        struct sigaction act;
        act.sa_handler = SIG_IGN;
        sigaction(SIGCHLD, &act, NULL);

        sleep(1);
        kill(pid, SIGUSR1);
        sleep(3);
        kill(pid, SIGUSR2);
        sleep(2);
        kill(pid, SIGQUIT);
    }

    return EXIT_SUCCESS;
}