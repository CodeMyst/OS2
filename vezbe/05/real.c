#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
        char* path;
        int cwd = 0;

        if (argc != 2) {
                cwd = 1;
                path = getcwd(NULL, 0);

                if (path == NULL) {
                        perror("error: ");
                        return -1;
                }
        } else {
                path = argv[1];
        }

        char resPath[PATH_MAX];

        char* res = realpath(path, resPath);

        if (res == NULL) {
                perror("error: ");
                return -1;
        }

        printf("%s\n", resPath);

        int depth = -1;
        for (int i = 0; i < strlen(resPath); i++) {
                if (resPath[i] == '/') depth++;
        }

        printf("depth: %d\n", depth);

        if (cwd) free(path);

        return 0;
}
