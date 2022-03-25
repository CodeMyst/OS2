#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("potrebna su 2 parametra\n");
		return 1;
	}

	char* parent = argv[1];
	char* name = argv[2];

	int res = chdir(parent);

	if (res == -1) {
		int err = errno;
		printf("greska: %s\n", strerror(err));
		return 1;
	}

	res = mkdir(name, 0700);

	if (res == -1) {
		int err = errno;
		printf("greska: %s\n", strerror(err));
		return 1;
	}

	return 0;
}
