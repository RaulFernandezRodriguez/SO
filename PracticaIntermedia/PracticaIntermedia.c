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
int randomizer(int max, int min);

int main(int argc, char*argv[]){ //coordinador es  padre
    struct sigaction ss;
    srand (time(NULL)); // getpid
    pid_t tecnico, encargado, asistentes, asis;
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
        asis = fork();
        if (asis == -1) {
            perror("Error en la llamada a fork()");
        } else if (asis == 0) {
            *(asistentes + i) = asis;
            pause();
        }
    }
    sleep(2);
    int vuelo = sigaction(SIGUSR1, &ss, NULL);
    pause();
    if(WIFSIGNALED(&status)){

    }else{
        if(WEXITSTATUS(&status) == 0){
            printf("El tecnico no ha considerado viable el vuelo, cancelando.\n");
                if(vuelo == 0){
                kill(tecnico, SIGTERM);
                kill(encargado, SIGTERM);
                for(int i = 0; i < sizeof(asistentes); i++){
                    kill(*(asistentes +i), SIGTERM);
                }
            }
        }else{
            printf("Nuestro tecnico ha considerado viable el vuelo, continuando");
            if(encargado){ //encargado
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
                    }
                    printf("Los %d pasajeros estan preparados para el vuelo, disfruten del viaje.\n", pasajeros);
                }
            }
        }
    }
    free(asistentes);
    return 0;
}

    void tecnicoHandler(int i){
        printf("Tecnico contactado.\n");
        sleep(randdomizer(6,3));
        exit(randomizer(1,0));
    }

    void encargadoHandler(int i){
        printf("Encargado contactado.\n");
        sleep(2);
        exit(randomizer(1, 0));
    }

    void asistenteHandler(int i){
        printf("Asistente %d contactado.\n", getpid());
        sleep(randomizer(6, 3));
        int pasajeros = randomizer(30, 20);
        printf("El asistente %d hay conseguido embarcar a unos %d pasajeros.\n", getpid(), pasajeros);
        exit(pasajeros);
    }

    int randomizer(int max, int min){
        srand(getpid());
        return rand() % (max - min +1) + min;
    }