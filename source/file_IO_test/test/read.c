#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char buf[1];
    int ret = 0;

    int fd1 = open(argv[1], O_WRONLY);
    if (fd1 == -1) {
        //printf("open error errno= %d\n", errno);
        //perror("open error");
        printf("open error : %s\n", strerror(errno));
        exit(1);
    }

    int fd2 = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, 0664);

    while ((ret = read(fd1, buf, sizeof(buf))) != 0) {
        write(fd2, buf, ret);
    }

    close(fd1);
    close(fd2);

    return 0;
}
