#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("sadrzaj trenutnog direktorijuma\n");

    int res = system("ls -flgG");

    if (res == -1) {
        perror("error");
        return -1;
    }

    printf("kraj ispisa\n");

    return 0;
}