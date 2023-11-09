#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void tecnico(int i);
void encargado(int i);
void asistente(int i);

int main(int argc, char*argv[]){ //coordinador es  padre
    srand (time(NULL));
    pid_t tecnico, encargado, a;
    tecnico = fork();
    if(tecnico == 0){
        pause();
    }
    encargado = fork(); 
    if(encargado == 0){
        pause();
    }
    int asistentes[argc];
    for (int i=0; i < argc; i++) {
        a = fork();
        if (a == -1) {
            perror("Error en la llamada a fork()");
        } else if (a == 0) {
            asistentes[i] = a;
            pause();
        }
    }

    sleep(2);
    int vuelo = signal(SIGUSR1, tecnico);
    if(vuelo == 0){
        kill(tecnico, SIGTERM);
        kill(encargado, SIGTERM)
        for(int i = 0; i < asistentes.length(); i++){
            kill(asistente[i], SIGTERM);
        }
    }

    int pasajeros = 0;
    int overbooking = signal(SIGUSR1, encargado);
    for(int i = 0; i < asistentes.length(); i++){
        pasajeros =  pasajeros + signal(SIGUSR2, asistentes[i]);
    }
    if(overbooking == 1){
        pasajeros = pasajeros -10;
    }
    printf(pasajeros);
}

    void tecnico(int i){
        printf("Tecnico contactado");
        sleep(rand() %4 + 3);
        exit(rand() %2 + 0);
    }

    void encargado(int i){
        printf("Encargado contactado");
        sleep(2);
        exit(rand() %2 + 0);
    }

    void asistente(int i){
        printf("Asistente" + getpid() + "contactado");
        sleep(rand() %4 + 3);
        exit(rand() %11 + 20);
    }