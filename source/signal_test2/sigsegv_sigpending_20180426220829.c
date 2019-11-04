#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *p = "hello";

void printset(const sigset_t *ped)
{
	int i;

	for(i = 0; i < 32; i++){
#if 0
		if(i == 8)
			p[2] = 'H';					
		if(sigismember(ped, 11))
			printf("SIGSEGV in blocked set\n");
#endif
		if((sigismember(ped, i) == 1))
			putchar('1');
		else 
			putchar('0');
	}
	printf("\n");
}

int main(void)
{
	sigset_t set, ped;

	sigemptyset(&set);
	sigaddset(&set, SIGSEGV);			
	sigaddset(&set, SIGINT);			
	sigaddset(&set, SIGTSTP);			

	sigprocmask(SIG_BLOCK, &set, NULL);			
	
	raise(SIGSEGV);

	while(1){
		sigpending(&ped);
		printset(&ped);
		sleep(1);
	}

	return 0;
}
