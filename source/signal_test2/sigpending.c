#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printset(sigset_t *ped)
{
	int i;
	for(i = 1; i < 32; i++){
		if((sigismember(ped, i) == 1)){
			putchar('1');
		} else {
			putchar('0');
		}
	}
	printf("\n");
}

int main(void)
{
	sigset_t set, ped;
#if 1
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
#else
	sigaddset(&set, SIGSEGV);
	sigaddset(&set, SIGKILL);
	sigaddset(&set, SIGQUIT);
	sigfillset(&set);
#endif
	sigprocmask(SIG_BLOCK, &set, NULL);	//不获取原屏蔽字

	while (1) {
		sigpending(&ped);               //获取未决信号集
		printset(&ped);
		sleep(1);
	}

	return 0;
}
