#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction act;
    act.sa_handler = SIG_IGN;

    sigaction(SIGINT, &act, NULL);

    while (1) {
        sleep(1);
    }

    return EXIT_SUCCESS;
}