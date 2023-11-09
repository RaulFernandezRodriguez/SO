#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    pid_t p;
    int array[5];

    for (int i=0; i<5; i++) {
        p = fork();
        if (p == -1) {
            perror("Error en la llamada a fork()");
        } else if (p == 0) {
            switch(i) {
                case 0:
                    execl("/usr/bin/xeyes", "xeyes", (char *)0);
                    break;
                case 1:
                    execl("/usr/bin/xload", "xload", (char *)0);
                    break;
                case 2:
                    execl("/usr/bin/xlogo", "xlogo", (char *)0);
                    break;
                
                case 3:
                    execl("/usr/bin/xcalc", "xcalc", (char *)0);
                    break;
                case 4:
                    execl("/usr/bin/xclock", "xclock", (char *)0);
                    break;
            }
        } else {
            array[i] = p;
        }
    }

    int status;

    p = wait(&status);

    while(p != -1) {
        pid_t newp;
        newp = fork();

        if (newp == -1) {
            perror("Error en la llamda fork()");

        } else if (newp == 0) {
            if (p == array[0]) execl("/usr/bin/xeyes", "xeyes", (char *)0);
            if (p == array[1]) execl("/usr/bin/xload", "xload", (char *)0);
            if (p == array[2]) execl("/usr/bin/xlogo", "xlogo", (char *)0);
            if (p == array[3]) execl("/usr/bin/xcalc", "xcalc", (char *)0);
            if (p == array[4]) execl("/usr/bin/xclock", "xclock", (char *)0);

        } else {
            if (p == array[0]) array[0] = newp;
            if (p == array[1]) array[1] = newp;
            if (p == array[2]) array[2] = newp;
            if (p == array[3]) array[3] = newp;
            if (p == array[4]) array[4] = newp;
        }
        p = wait(&status);
    }
    return 0;
}