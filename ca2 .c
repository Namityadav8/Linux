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
