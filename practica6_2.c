#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#define M 5.0 // Duración de la tarea del proceso padre
#define N 7.0 // Duración de la tarea del proceso padre
void hijo (int s);
void padre (int s);

int main(void){
    int x, i=0;
    pid_t pid, p_pid;
    struct sigaction ss;

    pid=fork();
    if (pid==-1){
        perror("Error en la llamada a fork()");
        exit(0);
    } else if (pid == 0){
        sigemptyset(&ss.sa_mask);
        ss.sa_flags = 0;
        ss.sa_handler = hijo;

        if(sigaction(SIGCONT, &ss, NULL)== -1){
            perror("Hijo, sigaction");
            return -1;
        }

        while(1){ 
            srand (getpid());
            x=1+(int)(N*rand()/ RAND_MAX +1.0);
            /* X es un número aleatorio entre 1 y N */
            printf("COMIENZO TAREA HIJO %d\n",i);
            sleep(x);
            printf("FIN TAREA HIJO %d\n",i);
            i++;
        }
    } else {
        while(1) {
            srand (getpid());
            x=1+(int)(M*rand()/ RAND_MAX +1.0);
            /* X es un número aleatorio entre 1 y N */
            printf("COMIENZO TAREA PADRE %d\n",i);
            sleep(x);
            // pause();
            printf("FIN TAREA PADRE %d\n",i);
            i++;
        }
    }
    return 0;
}