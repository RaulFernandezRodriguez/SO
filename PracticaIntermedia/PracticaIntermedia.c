#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void tecnicoHandler(int i);
void encargadoHandler(int i);
void asistenteHandler(int i);

int main(int argc, char*argv[]){ //coordinador es  padre
    struct sigaction ss;
    srand (time(NULL));
    pid_t tecnico, encargado, a;
    tecnico = fork();
    if(tecnico == 0){
        ss.sa_handler = &tecnicoHandler;
        pause();
    }
    encargado = fork(); 
    if(encargado == 0){
        ss.sa_handler = &encargadoHandler;  
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
    int vuelo = sigaction(SIGUSR1, &ss, NULL);
    pause();
    if(vuelo == 0){
        kill(tecnico, SIGTERM);
        kill(encargado, SIGTERM);
        for(int i = 0; i < asistentes.length(); i++){
            kill(asistente[i], SIGTERM);
        }
    }

    int pasajeros = 0;
    int overbooking = sigaction(SIGUSR1, &ss, NULL);
    pause();
    for(int i = 0; i < asistentes.length(); i++){
        pasajeros =  pasajeros + sigaction(SIGUSR2, &ss, NULL);//signal(SIGUSR2, asistentes[i]);
    }
    if(overbooking == 1){
        pasajeros = pasajeros -10;
    }
    printf(pasajeros);
}

    void tecnicoHandler(int i){
        printf("Tecnico contactado");
        sleep(rand() %4 + 3);
        exit(rand() %2 + 0);
    }

    void encargadoHandler(int i){
        printf("Encargado contactado");
        sleep(2);
        exit(rand() %2 + 0);
    }

    void asistenteHandler(int i){
        printf("Asistente" + getpid() + "contactado");
        sleep(rand() %4 + 3);
        exit(rand() %11 + 20);
    }