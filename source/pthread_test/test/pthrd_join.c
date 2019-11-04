#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int var;
    char str[64];
} exit_t;

void *tfn(void *arg)
{
    exit_t *ret = (exit_t *)arg;
    
    ret->var = 77;
    strcpy(ret->str, "hello pthread");

    pthread_exit((void *)ret);
}

int main(void)
{
    pthread_t tid;
    exit_t *ret = malloc(sizeof(exit_t));

    pthread_create(&tid, NULL, tfn, (void *)ret);
    pthread_join(tid, (void **)&ret);
    printf("pthred  var = %d, str= %s\n", ret->var, ret->str);

    return 0;
}


