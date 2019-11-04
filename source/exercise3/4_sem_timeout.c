#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 1024

sem_t s;

void *tfn(void *arg)
{
	char buf[N];

	while (1) {
		read(STDIN_FILENO, buf, N);         //读stdin无数据则阻塞
		sem_post(&s);                       //唤醒阻塞在信号量上的线程
	}

	return NULL;
}

int main(void)
{
	pthread_t tid;
	struct timespec t = {0, 0};

	sem_init(&s, 0, 0);                     //初始化信号量,初值为0
	pthread_create(&tid, NULL, tfn, NULL);

	t.tv_sec = time(NULL) + 1;              //绝对时间+1
	t.tv_nsec = 0;

	while (1) {
		sem_timedwait(&s, &t);              //限时阻塞信号量
		printf(" hello world\n");           //被post唤醒,或到达计时秒数
		t.tv_sec = time(NULL) + 5;          //重新计时
		t.tv_nsec = 0;
	}

	pthread_join(tid, NULL);                
	sem_destroy(&s);                        //销毁信号量

	return 0;
}
