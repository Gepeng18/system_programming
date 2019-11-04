#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(void)
{
	char buf[10];
	int fd, n;

	fd = open("/dev/tty", O_RDONLY|O_NONBLOCK); //使用O_NONBLOCK标志设置非阻塞读终端
	if(fd < 0){
		perror("open /dev/tty");
		exit(1);
	}
tryagain:

	n = read(fd, buf, 10);   //-1  (1)  出错  errno==EAGAIN或者EWOULDBLOCK

	if(n < 0){
		//由于open时指定了O_NONBLOCK标志，read读设备，没有数据到达返回-1，同时将errno设置为EAGAIN或EWOULDBLOCK
		if(errno != EAGAIN){		//也可以是 if(error != EWOULDBLOCK)两个宏值相同
			perror("read /dev/tty");
			exit(1);
		}
		sleep(3);
		write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
		goto tryagain;
	}
	write(STDOUT_FILENO, buf, n);
	close(fd);

	return 0;
}
