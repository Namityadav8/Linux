#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("P1 (Parent), PID: %d\n", getpid());

    
    pid_t p2 = fork();

    if (p2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (p2 == 0) {
        printf("P2 (Child of P1), PID: %d, Parent PID: %d\n", getpid(), getppid());

        
        pid_t p3 = fork();

        if (p3 < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (p3 == 0) {
            printf("P3 (Child of P2), PID: %d, Parent PID: %d\n", getpid(), getppid());

            pid_t p4 = fork();

            if (p4 < 0) {
                perror("Fork failed");
                exit(1);
            }

            if (p4 == 0) {
                printf("P4 (Orphan), PID: %d, Parent PID: %d\n", getpid(), getppid());
                sleep(2); 
                printf("P4 is now an orphan, Parent PID: %d\n", getppid());
            } else {
                exit(0); 
            }
        } else {
          
            wait(NULL);
            printf("P2 (Child of P1) exiting\n");
        }
    } else {
        wait(NULL);
        printf("P1 (Parent) exiting\n");
    }

    pid_t p5 = fork();

    if (p5 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (p5 == 0) {
        printf("P5 (Zombie), PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0);
    } else {
        printf("Parent (P1) sleeping, leaving P5 as a zombie.\n");
        sleep(5);
    }

    return 0;
}