#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
	int res = mkdir("os2", 0700);

	if (res == -1) {
		int err = errno;
		printf("greska: %s\n", strerror(err));
	}

	return 0;
}
