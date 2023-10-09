#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> // Include sys/types.h for wait

void createProcess(int level) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("P%d (PID %d, PPID %d)\n", level, getpid(), getppid());
        if (level < 3) { // Adjust the depth of the hierarchy here (e.g., 3 for P1 -> P2 -> P3)
            createProcess(level + 1);
        }
        exit(0);
    } else {
        // Parent process
        wait(NULL);
    }
}

int main() {
    printf("P1 (PID %d, PPID %d)\n", getpid(), getppid());
    createProcess(2); // Start with level 2 to create P2 and its children
    
    return 0;
}
