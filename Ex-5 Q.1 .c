#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Please provide a positive integer for n.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            printf("Child process %d (PID %d)\n", i, getpid());
            return 0;
        }
    }

    printf("Parent process (PID %d) created %d child processes\n", getpid(), n);

    return 0;
}
