#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *desktopPath = "/home/your-username/Desktop"; 
    const char *newDirName = "mydir";
    const char *newFileName = "myfile.txt";
    char newDirPath[1024];
    char newFilePath[1024];

    snprintf(newDirPath, sizeof(newDirPath), "%s/%s", desktopPath, newDirName);
    if (mkdir(newDirPath, 0777) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    snprintf(newFilePath, sizeof(newFilePath), "%s/%s", newDirPath, newFileName);
    FILE *file = fopen(newFilePath, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Hello, World!\n");
    fclose(file);

    printf("Contents of directory %s:\n", newDirPath);
    struct dirent *entry;
    DIR *dir = opendir(newDirPath);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dir))) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *threadFunction(void *arg) {
    char *str = (char *)arg;
    int len = strlen(str);
    printf("String Length: %d\n", len);
    return NULL;
}

int main() {
    // p1
    printf("p1 (Parent) - PID: %d\n", getpid());

    // p2
    pid_t child1 = fork();
    if (child1 == 0) {
        // p2
        printf("p2 - PID: %d, Parent PID: %d\n", getpid(), getppid());

        // p3
        pid_t child2 = fork();
        if (child2 == 0) {
            // p3
            printf("p3 - PID: %d, Parent PID: %d\n", getpid(), getppid());
            exit(0);
        }

        // p4 (inside p2)
        pid_t child3 = fork();
        if (child3 == 0) {
            // p4
            printf("p4 - PID: %d, Parent PID: %d\n", getpid(), getppid());
            exit(0);
        }

        exit(0);
    }

    // p5
    pid_t child4 = fork();
    if (child4 == 0) {
        // p5
        printf("p5 - PID: %d, Parent PID: %d\n", getpid(), getppid());

        // p6
        pid_t child5 = fork();
        if (child5 == 0) {
            // p6
            printf("p6 - PID: %d, Parent PID: %d\n", getpid(), getppid());

            // Create a thread to check the length of a string
            pthread_t thread;
            char str[] = "Hello, World!";
            pthread_create(&thread, NULL, threadFunction, (void *)str);
            pthread_join(thread, NULL);

            exit(0);
        }

        // p7 (inside p5)
        pid_t child6 = fork();
        if (child6 == 0) {
            // p7
            printf("p7 - PID: %d, Parent PID: %d\n", getpid(), getppid());
            exit(0);
        }

        exit(0);
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 7; i++) {
        wait(NULL);
    }

    return 0;
}
