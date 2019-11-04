#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

/*
struct itimerval {

    struct timeval {
        time_t      tv_sec;        
        suseconds_t tv_usec;      
    }it_interval; 

    struct timeval {
        time_t      tv_sec;      
        suseconds_t tv_usec;    
    }it_value;    

} it, oldit;
*/

unsigned int my_alarm(unsigned int seconds){
    struct itimerval it, oldit;

    it.it_value.tv_sec = seconds;
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &it, &oldit);
    if (ret == -1) {
        perror("setitimer error");
        exit(1);
    }

    return oldit.it_value.tv_sec;
}

int main(void)
{
    int i = 1;
    my_alarm(1);

    while (1) 
        printf("%d\n", i++);

    return 0;
}
