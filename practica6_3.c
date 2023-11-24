#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void actualtime(int hours);

int main(void){
    signal(SIGALRM, actualtime);
    system("date");
    while(1){
        alarm(10);
        pause();
    }
}

void actualtime(int hours){
    system("date");
    alarm(10);
}