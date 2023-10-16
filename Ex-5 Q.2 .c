#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

void createProcess(int level) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        
        printf("P%d (PID %d, PPID %d)\n", level, getpid(), getppid());
        if (level < 3) { 
            createProcess(level + 1);
        }
        exit(0);
    } else {
        
        wait(NULL);
    }
}

int main() {
    printf("P1 (PID %d, PPID %d)\n", getpid(), getppid());
    createProcess(2); 
    
    return 0;
}
