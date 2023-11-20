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
    int num_Asistentes = atoi(argv[1]);
    printf("Tenemos %d asistentes.\n", num_Asistentes);
    struct sigaction ss;
    srand(time(NULL));
    pid_t tecnico, encargado, *asistentes, actual;
    actual = fork();
    if(actual == -1){
        printf("Error al contratar a un tecnico, estan en huelga, cancelando...\n");
       return 1;
    }
    tecnico = actual;
    if(actual != 0){
        actual = fork();
        if(actual == -1){
            perror("Error al contratar a un encargado, LinkedIn estaba caido, cancelando...\n");
            return 1;
        }
        encargado = actual;
    }            
    if(tecnico == 0){
        ss.sa_handler = &tecnicoHandler;
        if(sigaction(SIGUSR1, &ss, NULL) == -1){
            perror("Error al contactar al tecnico, estara tomando la siesta, cancelando...\n");
            return 1;
        }
        pause();
    }else if(encargado == 0){
        ss.sa_handler = &encargadoHandler;
        if(sigaction(SIGUSR1, &ss, NULL) == -1){
            perror("Error al contactar al encargado, para esto le pagamos, cancelando...\n");           
        }
        pause();
    }else{ //coordinator
        asistentes = (pid_t *)malloc(sizeof(pid_t) * num_Asistentes);
        for (int i=0; i < num_Asistentes; i++) {
            actual = fork();
            if (actual == -1) {
                perror("Error al llamar a los asistentes, asi no se puede seguir...\n");
                return 1;
            } else if (actual == 0) {   
                ss.sa_handler = &asistenteHandler;
                if(sigaction(SIGUSR2, &ss, NULL) == -1){
                    perror("Error al configurar a los asistentes, cancelando...\n");
                    return 1;
                }
                printf("Asistente contratado via entevista de trabajo.\n");
                pause();
            }else{
                *(asistentes + i) = actual;
            }
        }
        sleep(2);
        kill(tecnico, SIGUSR1);
        int status;
        wait(&status);
        if(!WIFEXITED(status)){
            printf("Algo ha ocurrido con el tecnico, tendremos que cancelar...\n");
            return 1;
        }else{
            if(WEXITSTATUS(status) == 1){
                printf("El tecnico NO ha considerado viable el vuelo, cancelando.\n");
                kill(tecnico, SIGTERM);
                kill(encargado, SIGTERM);
                for(int i = 0; i < sizeof(asistentes); i++){
                    kill(*(asistentes +i), SIGTERM);
                }
                return 1;
            }else{
                printf("Nuestro tecnico ha considerado viable el vuelo, continuando\n");
                kill(encargado, SIGUSR1);
                int overbooking;
                wait(&status);
                if(!WIFEXITED(status)){
                    printf("Algo ha ocurrido con el encargado, tendremos que cancelar.....\n");
                    return 1;
                }
                overbooking = WEXITSTATUS(status);
                int pasajeros = 0;
                printf("Vamos a ir registrando los pasajeros.\n");
                for(int i = 0; i < num_Asistentes; i++){
                    kill(*(asistentes +i), SIGUSR2);
                }
                for(int i = 0; i < num_Asistentes; i++){
                    wait(&status);
                    pasajeros = pasajeros + WEXITSTATUS(status);  
                }
                if(overbooking == 1){
                    printf("Buf,se nos ha ido de manos el planteamiento y hemos tenido overbooking.\n");
                    pasajeros = pasajeros -10;
                }
                printf("Los %d pasajeros estan preparados para el vuelo, disfruten del viaje.\n", pasajeros);     
            }
        }
    }
    free(asistentes);
    return 0;
}

    void tecnicoHandler(int i){
        printf("Tecnico contactado.\n");
        sleep(randomizer(6,3));
        exit(randomizer(2,1));
    }

    void encargadoHandler(int i){
        printf("Encargado contactado.\n");
        sleep(2);
        exit(randomizer(2, 1));
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