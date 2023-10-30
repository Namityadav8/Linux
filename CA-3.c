#include <stdio.h>
#include <unistd.h>
#include <string.h>

void *thread(void *arg) {
    char *str = (char *)arg;
    printf("string length is : %lu\n", strlen(str));
    return NULL;
}

int main() {
    pid_t pids[7];

    for (int i = 0; i < 7; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            printf("p%d - PID: %d, Parent pid: %d\n", i + 1, getpid(), getppid());

            if (i == 5) { 
                char str[] = "Hi there ! ";
                pthread_t thread;
                pthread_create(&thread, NULL, thread, (void *)str);
                pthread_join(thread, NULL);
            }

            exit(0);
        }
    }

    for (int i = 0; i < 7; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}
