#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    int fd = open("./mydir", O_WRONLY);
    printf("fd = %d\n", fd);
    printf("errno= %d\n", errno);

    close(fd);
    printf("close ok...\n");

    return 0;
}
