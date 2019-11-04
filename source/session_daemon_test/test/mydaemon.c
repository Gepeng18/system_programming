#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

void mydaemon(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid > 0) {
        exit(1);
    }

    pid = setsid();
    if (pid < 0) {
        perror("setsdi error");
        exit(1);
    }

    if (chdir("/") < 0) {
        perror("chdir error");
        exit(1);
    }

    umask(0022);

    close(0);
    int fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    
    return ;
}

int main(void)
{
    mydaemon();
    while (1) ;     //守护进程功能

    return 0;
}
