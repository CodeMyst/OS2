#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("sadrzaj trenutnog direktorijuma\n");

    pid_t child = fork();
    int wstatus;

    if (child == -1) {
        perror("error");
        exit(EXIT_FAILURE);
    }

    if (child == 0) {
        int res = execl("/bin/ls", "-f", "-l", "-g", "-G", NULL);

        if (res == -1) {
            perror("error");
            exit(EXIT_FAILURE);
        }
    } else {
        pid_t wpid = waitpid(child, &wstatus, 0);

        if (WIFEXITED(wstatus)) {
            printf("kraj ispisa\n");
        } else {
            printf("error\n");
        }
    }

    return 0;
}