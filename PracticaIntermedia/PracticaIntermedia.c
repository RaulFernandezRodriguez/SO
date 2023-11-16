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
    srand (time(NULL)); // getpid
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
    asistentes = (pid_t *)malloc(sizeof(pid_t) * argc);
    for (int i=0; i < argc; i++) {
        a = fork();
        if (a == -1) {
            perror("Error en la llamada a fork()");
        } else if (a == 0) {
            *(asistentes + i) = a;
            pause();
        }
    }

    sleep(2);
    int vuelo = sigaction(SIGUSR1, &ss, NULL);
    pause();
    if(vuelo == 0){
        kill(tecnico, SIGTERM);
        kill(encargado, SIGTERM);
        for(int i = 0; i < sizeof(asistentes); i++){
            kill(*(asistentes +i), SIGTERM);
        }
    }


    int overbooking = sigaction(SIGUSR1, &ss, NULL);
    pause(); 
    if(coordinador){
        int pasajeros = 0;
    for(int i = 0; i < sizeof(asistentes); i++){
        kill(*(asistentes), SIGUSR2);
    }
    while(pid != -1){
        pid = wait(&status);
        if(WIFSIGNALED(wstatus)){
            
        }
        pasajeros = pasajeros + WEXITSTATUS(status);
        
    }
    if(overbooking == 1){
        printf("Buf,se nos ha ido de manos el planteamiento y hemos tenido overbooking");
        pasajeros = pasajeros -10;
    }printf("Los %d pasajeros estan preparados para el vuelo, disfruten del viaje.\n", pasajeros);
    }
    
    free(asistentes);
    
}

    void tecnicoHandler(int i){
        printf("Tecnico contactado.\n");
        sleep(rand() %4 + 3);
        exit(rand() %2 + 0);
    }

    void encargadoHandler(int i){
        printf("Encargado contactado.\n");
        sleep(2);
        exit(rand() %2 + 0);
    }

    void asistenteHandler(int i){
        printf("Asistente %d contactado.\n", getpid());
        sleep(rand() %4 + 3);
        int pasajeros = rand() % 11 +20;
        printf("El asistente %d hay conseguido embarcar a unos %d pasajeros.\n", getpid(), pasajeros);
        exit(pasajeros);
    }