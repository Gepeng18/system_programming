#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sig_child(int signo)
{
    pid_t wpid;
    int status;

    while ((wpid = waitpid(0, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("--------------child exit with %d\n", WEXITSTATUS(status));
        } 
    }
}

int main(void)
{
    int i;
    pid_t pid;
//阻塞
    for (i = 0; i < 10; i++) {
        if ((pid = fork()) == 0)
            break;
    }

    if (i != 10) {
        printf("child process pid = %d\n", getpid());
        return i+1;
    } else if (i == 10) {
        struct sigaction act;

        act.sa_handler = sig_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGCHLD, &act, NULL);
//解除阻塞
        
        while (1) {
            printf("parent pid = %d\n", getpid());
            sleep(1);
        }
    }

    return 0;
}
