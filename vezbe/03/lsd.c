#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int list(char* path) {
	DIR* dir = opendir(path);

	if (dir == NULL) {
		int err = errno;
		printf("%s\n", strerror(err));
		return 1;
	}

	while (1) {
		// to distinguish end of stream and error, set errno to zero before calling readdir
		errno = 0;
		struct dirent* entry = readdir(dir);

		if (entry == NULL) {
			if (errno != 0) {
				printf("%s\n", strerror(errno));
				return 1;
			}

			break;
		}

		// ignore "." and ".." dirs
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

		// ignore hidden entries
		if (entry->d_name[0] == '.') continue;

		// get child path
		char childPath[256];
		strcpy(childPath, path);
		strcat(childPath, "/");
		strcat(childPath, entry->d_name);
		
		// get rid of extra /
		char childResolvedPath[256];
		realpath(childPath, childResolvedPath);

		// get entry stats
		struct stat stats;
		if (stat(childResolvedPath, &stats) == -1) {
			int err = errno;
			printf("%s\n", strerror(err));
			return 1;
		}

		char type;
		if (S_ISREG(stats.st_mode)) {
			type = '-';
		} else if (S_ISDIR(stats.st_mode)) {
			type = 'd';
		} else if (S_ISCHR(stats.st_mode)) {
			type = 'c';
		} else if (S_ISBLK(stats.st_mode)) {
			type = 'b';
		} else if (S_ISFIFO(stats.st_mode)) {
			type = 'f';
		} else if (S_ISLNK(stats.st_mode)) {
			type = 'l';
		} else if (S_ISSOCK(stats.st_mode)) {
			type = 's';
		}

		char perms[] = "rwxrwxrwx";

		if (!(stats.st_mode & S_IRUSR)) {
			perms[0] = '-';
		}
		if (!(stats.st_mode & S_IWUSR)) {
			perms[1] = '-';
		}
		if (!(stats.st_mode & S_IXUSR)) {
			perms[2] = '-';
		}

		if (!(stats.st_mode & S_IRGRP)) {
			perms[3] = '-';
		}
		if (!(stats.st_mode & S_IWGRP)) {
			perms[4] = '-';
		}
		if (!(stats.st_mode & S_IXGRP)) {
			perms[5] = '-';
		}

		if (!(stats.st_mode & S_IROTH)) {
			perms[6] = '-';
		}
		if (!(stats.st_mode & S_IWOTH)) {
			perms[7] = '-';
		}
		if (!(stats.st_mode & S_IXOTH)) {
			perms[8] = '-';
		}

		struct tm* time = localtime(&stats.st_ctime);

		printf("%c%s %ld %8ld %d-%02d-%02d %02d:%02d %s\n", type, perms, stats.st_nlink, 512 * stats.st_blocks, 1900 + time->tm_year, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, entry->d_name);
	}

	if (closedir(dir) == -1) {
		int err = errno;
		printf("%s\n", strerror(err));
		return 1;
	}

	return 0;
}

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		int res = list(argv[i]);
		if (res != 0) return res;
	}

	return 0;
}
