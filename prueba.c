#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
void handler(int pid){
	kill(pid, SIGTERM);
}
int main(void){
	pid_t pid, p_pid;
	int estado, senal, end;
	pid = fork();
	switch(pid){
		case -1: perror("Fallo") ; exit(0); break;
		case 0: 
			pid = wait(10);
			exit(0);
			break;
		case 1: 
			signal(SIGINT, handler);	
			
			estado = WEXITSTATUS(pid);
			printf(" %d ", estado);
			senal = WTERMSIG(pid);
			printf(" %d ", senal);
			printf("No se ha hecho nada, hijo sigue vivo");
			exit(0);
			break;
	}
}
