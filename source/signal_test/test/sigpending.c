#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void printset(sigset_t *ped)
{
    int i;
    for (i = 1; i < 32; i++) {
        if (sigismember(ped, i) == 1) {
            putchar('1');
        } else 
            putchar('0');
    }
    printf("\n");
}

int main(void)
{
    sigset_t set, oldset, ped;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGKILL);
    sigaddset(&set, SIGTSTP);
    sigaddset(&set, SIGSTOP);

    sigprocmask(SIG_BLOCK, &set, &oldset);

    while (1) {
        sigpending(&ped);
        printset(&ped);
        sleep(1);
    }

    return 0;
}
