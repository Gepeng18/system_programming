#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(void)
{
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        sleep(1);
        printf("child pid = %d, ppid = %d\n", getpid(), getppid());
        kill(getppid(), SIGCHLD);

    } else if (pid > 0) {
        while (1) {
            printf("parent pid = %d, ppid= %d\n", getpid(), getppid());
            sleep(1);
        }
    }

    return 0;
}
