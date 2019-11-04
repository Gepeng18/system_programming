#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define T_NUM 5             //默认线程数5
#define ITEMS 66            //'='的个数

void err_sys(void *str)
{
	perror(str);
	exit(1);
}
void err_usr(char *str)
{
	fputs(str, stderr);
	exit(1);
}

/*每个线程都对应如下3个属性*/
typedef struct {             
	int off;    //拷贝的起始位置
    int size;   //拷贝的长度
    int t_no;   //自己是第几个被创建的线程
} arg_t;

char *s, *d;
int *done;      //为一个数组,每个元素记录每个线程完成任务字节数
int n = T_NUM;

void *tfn(void *arg)
{
	arg_t *arg_p; 
    int i;
	char *p, *q;

	arg_p = (arg_t *)arg;   //每个线程自己的结构体 arg{off, size, t_no}

	p = s + arg_p->off;     //当前线程执行拷贝任务,在原文件中的起始位置
    q = d + arg_p->off;     //目标文件的起始位置

    //每个线程按字节拷贝自己的任务,并将拷贝字节数写入字节对应的done数组中
	for (i = 0; i < arg_p->size; i++) {
		*q++ = *p++; 
        done[arg_p->t_no]++;   
		usleep(100);
	}

	return NULL;
}

void *display(void *arg)
{
	int size, interval, draw, sum, i, j;

	size = (int)arg;                        //文件总大小

	interval = size / ITEMS;                //每个'='所代表的字节数
	draw = 0;                               //画出的'='的个数

	while (draw < ITEMS) {
		for (i = 0, sum = 0; i < n; i++)    //借助done数组获取当前已经拷贝的总字节数
			sum += done[i];

		j = sum / interval;                 //计算到当前应该打印多少个'='

		for (; j > draw; draw++) {          //输出与线程拷贝字节数相对应个数的'='
			putchar('='); 
            fflush(stdout);
		}
	}
	putchar('\n');

	return NULL;
}

int main(int argc, char *argv[])
{
	int src, dst, i, len, off;
	struct stat statbuf;

	pthread_t *tid;
	arg_t *arr;

	if (argc != 3 && argc != 4) 
		err_usr("usage : cp src dst [thread_no]\n");
	if (argc == 4)
		n = atoi(argv[3]);      //用户指定线程数,默认值5

	src = open(argv[1], O_RDONLY);
	if (src == -1)
		err_sys("fail to open");
	dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dst == -1)
		err_sys("fail to open");

	if (fstat(src, &statbuf) == -1)
		err_sys("fail to stat");

    ftruncate(dst, statbuf.st_size);

    //源文件映射区首地址,保存在 全局变量s中
	s = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, src, 0);
	if (s == MAP_FAILED)
		err_sys("fail to mmap");

    //目标文件映射区首地址,保存在 全局变量d中
	d = (char *)mmap(NULL, statbuf.st_size, PROT_WRITE , MAP_SHARED, dst, 0);
	if (d == MAP_FAILED)
		err_sys("fail to mmap");

	close(src); close(dst);

    //pthread_t tid[n+1];   线程ID数组分配空间
	tid = (pthread_t *)malloc(sizeof(pthread_t) * (n+1));
	if (tid == NULL)
		err_sys("fail to malloc");

    //int done[n]   为int *done分配空间 
	done = (int *)calloc(sizeof(int), n);
	if (done == NULL)
		err_sys("fail to calloc");

    //arr[n]    为结构体数据arr分配空间 
	arr = (arg_t *)malloc(sizeof(arg_t) * n);
	if (arr == NULL)
		err_sys("fail to malloc");

    //计算每个线程应拷贝字节数, 起始偏移位置归零
	len = statbuf.st_size / n, off = 0;

    //计算出每个线程拷贝的起始地址, 对应i写入结构体数组arr
	for (i = 0; i < n; i++, off += len) 
		arr[i].off = off, arr[i].size = len, arr[i].t_no = i; 

    //调整下最后一个线程拷贝的字节个数
	arr[n-1].size += (statbuf.st_size % n);
    
    //创建拷贝线程, 对应i将每个线程arr[i]中记录的应拷贝的任务,传入线程主函数
	for(i = 0; i < n; i++)
		pthread_create(&tid[i], NULL, tfn, (void *)&arr[i]);

    //创建进度线程, 传入文件总大小
	pthread_create(&tid[n], NULL, display, (void *)statbuf.st_size);

    //回收子线程
	for(i = 0; i < n+1; i++)
		pthread_join(tid[i], NULL);

	munmap(s, statbuf.st_size);
	munmap(d, statbuf.st_size);
	free(tid); free(done); free(arr);

	return 0;
}

