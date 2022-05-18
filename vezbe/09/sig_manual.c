#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int should_exit = 0;

void handle_signal(int signal) {
    should_exit = 1;
}

int main(void) {
    struct sigaction act;
    act.sa_handler = &handle_signal;

    sigaction(SIGINT, &act, NULL);

    while (1) {
        if (should_exit) {
            printf("epik signal\n");
            exit(EXIT_SUCCESS);
        }

        sleep(1);
    }

    return EXIT_SUCCESS;
}
