#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void sig_int(int signo)
{
    printf("---------catch you!!!! SIGINT, signo=%d\n", signo);
    sleep(10);
}

int main(void)
{
    struct sigaction act, oldact;

    act.sa_handler = sig_int;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, &oldact);

    while (1);

    return 0;
}
