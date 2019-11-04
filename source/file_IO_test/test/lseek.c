#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
	int fd, n;
	char msg[] = "It's a test for lseek\n";
	char ch;

	fd = open("lseek.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if(fd < 0){
		perror("open lseek.txt error");
		exit(1);
	}

    lseek(fd, 100, SEEK_SET);
    int ret = lseek(fd, 0, SEEK_SET);
    if (ret == -1) {
        perror("lseek error");
        exit(1);
    }
    write(fd, "\0", 1);

    int len = lseek(fd, 0, SEEK_END);
    printf("file len = %d\n", len);

	close(fd);

	return 0;
}
