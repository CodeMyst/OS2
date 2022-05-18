#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int tried_to_exit = 0;

void handle_signal(int signal) {
    tried_to_exit++;
}

int main(void) {
    struct sigaction act;
    act.sa_handler = &handle_signal;

    sigaction(SIGINT, &act, NULL);

    while (1) {
        if (tried_to_exit >= 4) {
            printf("you killed me after all :(\n");
            exit(EXIT_SUCCESS);
        }

        sleep(1);
        printf("tried to exit %d times\n", tried_to_exit);
    }

    return EXIT_SUCCESS;
}