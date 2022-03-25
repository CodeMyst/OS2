#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct options {
	int recursive;
	int showHidden;
} options;

int list(options opts, char* path, int indentLevel) {
	// dont print full path when recursive
	if (indentLevel == 0) printf("%s:\n", path);

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

		// ignore hidden entries, unless showHidden is enabled
		if (entry->d_name[0] == '.' && !opts.showHidden) continue;

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

		for (int i = 0; i < indentLevel; i++) printf("  ");
		printf("  %ld %s\n", stats.st_nlink, entry->d_name);

		if (opts.recursive) {
			// if the entry is a dir, recurse
			if (entry->d_type == DT_DIR) {
				list(opts, childResolvedPath, indentLevel + 1);
			}
		}
	}

	if (closedir(dir) == -1) {
		int err = errno;
		printf("%s\n", strerror(err));
		return 1;
	}

	return 0;
}

void parseOptions(int argc, char** argv, options* opts) {
	opts->recursive = 0;
	opts->showHidden = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (strcmp(argv[i], "-R") == 0) {
				opts->recursive = 1;
			} else if (strcmp(argv[i], "-a") == 0) {
				opts->showHidden = 1;
			} else {
				printf("unknown option %s\n", argv[i]);
			}
		}
	}
}

int main(int argc, char** argv) {
	options opts;
	parseOptions(argc, argv, &opts);

	for (int i = 1; i < argc; i++) {
		// ignore options
		if (argv[i][0] != '-') {
			int res = list(opts, argv[i], 0);
			if (res != 0) return res;
		}
	}

	return 0;
}
