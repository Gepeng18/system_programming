#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(void)
{
    while (1) {
        printf("pid = %d\n", getpid());
        sleep(1);
        abort();
    }
    return 0;
}
