#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *tfn(void *arg)
{
    int i = *((int *)arg);
    sleep(i);
    printf("I'm %dth pthread   tid = %lu\n", i+1, pthread_self());

    return NULL;
}
int main(void)
{
    pthread_t tid;
    int i, ret;
    for (i = 0; i < 5; i++) {
        ret = pthread_create(&tid, NULL, tfn, (void *)&i);
        if (ret != 0) {
            fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
            exit(1);
        }
    }
    sleep(i);
    printf("----I'm main pthread  tid = %lu\n", pthread_self());

    return 0;
}


