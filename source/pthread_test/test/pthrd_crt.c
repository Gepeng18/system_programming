#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *tfn(void *arg)
{
    printf("tfn-- pid = %d, tid = %lu\n", getpid(), pthread_self());
    return (void *)0;
}

int main(void)
{
    pthread_t tid;
    printf("main -- pid = %d, tid = %lu\n", getpid(), pthread_self());

    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0) {
        //printf("pthread_create erro: %s\n", strerror(ret));
        fprintf(stderr, "pthread_create erro: %s\n", strerror(ret));
        exit(1);
    }
    sleep(1);

    return 0;
}


