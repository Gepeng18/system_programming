#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(void)
{
    int i = 1;
    alarm(1);

    while (1) {
        printf("%d\n", i++);
    }

    return 0;
}
