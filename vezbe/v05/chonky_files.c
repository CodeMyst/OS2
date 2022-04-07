#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char** argv) {
        if (argc < 2) {
                printf("one path required.\n");
                return -1;
        }

        long int min = 100;

        for (int i = 1; i < argc; i++) {
                char* endptr;
                long int res = strtol(argv[i], &endptr, 10);

                if (*endptr == '\0') min = res;
        }

        DIR* dir = opendir(argv[1]);

        if (dir == NULL) {
                perror("error opening the provided dir");
                return -1;
        }

        while (1) {
                struct dirent* entry = readdir(dir);

                errno = 0;
                if (entry == NULL) {
                        if (errno != 0) {
                                perror("error reading a dir");
                                return -1;
                        }

                        break;
                }

                char childPath[PATH_MAX];
                strcpy(childPath, argv[1]);
                strcat(childPath, "/");
                strcat(childPath, entry->d_name);

                struct stat st;
                if (stat(childPath, &st) == -1) {
                        perror("error getting file stats");
                        return -1;
                }

                unsigned long kbSize = st.st_size / 1024;

                if (kbSize <= min) continue;

                printf("%s %ld %ld\n", entry->d_name, st.st_nlink, kbSize);
        }

        if (closedir(dir) == -1) {
                perror("error closing the provided dir");
        }

        return 0;
}
