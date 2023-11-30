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
    if(argc != 2){
        perror("Numero de entradas invalida, cancelando.\n");
        return 1;
    }
    printf("------------------------------------------------------------------\n");
    printf("Buenas, gracias por confiar en vuelos ULE, empezamos con los preparativos.\n");
    int num_Asistentes = atoi(argv[1]);
    if(num_Asistentes < 1){
        perror("Numero erroneo de asistentes, cancelando vuelo...\n");
        return 1;
    }
    printf("Tenemos que contratar %d asistentes.\n", num_Asistentes);
    struct sigaction ss;
    int status;
    srand(time(NULL));
    pid_t tecnico, encargado, *asistentes, actual;
    actual = fork(); // Creamos hijo tecnico
    if(actual == -1){
        printf("Error al contratar a un tecnico, estan en huelga, cancelando...\n");
       return 1;
    }
    tecnico = actual;
    if(actual != 0){ // Creamos hijo encargado
        actual = fork();
        if(actual == -1){
            perror("Error al contratar a un encargado, LinkedIn estaba caido, cancelando...\n");
            return 1;
        }
        encargado = actual;
    }            
    if(tecnico == 0){ // Asignamos el tecnico su handler
        ss.sa_handler = &tecnicoHandler;
        if(sigaction(SIGUSR1, &ss, NULL) == -1){
            perror("Error al contactar al tecnico, estara tomando la siesta, cancelando...\n");
            return 1;
        }
        printf("Tecnico contratado con exito.\n");
        pause();
    }else if(encargado == 0){ // Y asignamos tambien al encargado su handler
        ss.sa_handler = &encargadoHandler;
        if(sigaction(SIGUSR1, &ss, NULL) == -1){
            perror("Error al contactar al encargado, para esto le pagamos, cancelando...\n");           
        }
        printf("Encargado contratado con exito.\n");
        pause();
    }else{ //Finalmente el coordinador (padre) creara los hijos asistentes y les asignara con ello su handler
        asistentes = (pid_t *)malloc(sizeof(pid_t) * num_Asistentes);
        for (int i=0; i < num_Asistentes; i++) {
            actual = fork();
            if (actual == -1) {
                perror("Error al llamar a los asistentes, asi no se puede seguir...\n");
                return 1;
            } else if (actual == 0) {   // A la vez les vamos asignando su handler a la que los creamos
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
        sleep(2); // Con todos los hijos creados, empezamos el funcionamiento del vuelo
        kill(tecnico, SIGUSR1);
        wait(&status); // Mandamos señal al tecnico, si la señal falla o el tecnico considera inviable el vuelo, cancelamos la ejecucion y matamos a todos los hijos
        if(!WIFEXITED(status)){
            printf("Algo ha ocurrido con el tecnico, tendremos que cancelar...\n");
            kill(tecnico, SIGTERM);
            kill(encargado, SIGTERM);
            for(int i = 0; i < sizeof(asistentes); i++){
                kill(*(asistentes +i), SIGTERM);
            }
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
                printf("Nuestro tecnico ha considerado viable el vuelo, continuando.\n");
                kill(encargado, SIGUSR1);
                int overbooking;
                wait(&status); // Si todo funciona, llamamos al encargado para ver si hay overbooking
                if(!WIFEXITED(status)){ // igual que antes, si falla la señal (no acabo con un exit), cancelamos todo
                    printf("Algo ha ocurrido con el encargado, tendremos que cancelar...\n");
                    kill(tecnico, SIGTERM);
                    kill(encargado, SIGTERM);
                    for(int i = 0; i < sizeof(asistentes); i++){
                        kill(*(asistentes +i), SIGTERM);
                    }
                    return 1;
                }
                overbooking = WEXITSTATUS(status);
                int pasajeros = 0;
                printf("Vamos a ir registrando los pasajeros.\n");
                for(int i = 0; i < num_Asistentes; i++){
                    kill(*(asistentes +i), SIGUSR2);
                } // Contactamos a todos los hijos asistentes a la vez para que saquen un numero aleatorio de pasajeros
                for(int i = 0; i < num_Asistentes; i++){
                    wait(&status);
                    pasajeros = pasajeros + WEXITSTATUS(status);  
                } // Una vez sumados todos los pasajeros le restamos 10 si hubo overbooking al llamar al encargado
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