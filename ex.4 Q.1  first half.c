#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
    char *desktop_path = getenv("HOME");
    char directory_name[] = "MyDirectory";
    char file_name[] = "example.txt";

    
    char directory_path[256];
    snprintf(directory_path, sizeof(directory_path), "%s/Desktop/%s", desktop_path, directory_name);
    mkdir(directory_path, 0777);

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", directory_path, file_name);
    int fd = open(file_path, O_CREAT | O_WRONLY, 0644);
    if (fd != -1) {
        const char *content = "This is a sample file created on the desktop.\n";
        write(fd, content, strlen(content));
        close(fd);
    } else {
        perror("Error creating file");
        return 1;
    }

   
    printf("Contents of '%s' on the desktop:\n", directory_name);
    struct dirent *entry;
    DIR *dir = opendir(directory_path);
    if (dir) {
        while ((entry = readdir(dir))) {
            if (entry->d_type == DT_REG) {
                printf("File: %s\n", entry->d_name);
            } else if (entry->d_type == DT_DIR) {
                printf("Directory: %s\n", entry->d_name);
            } else {
                printf("Unknown: %s\n", entry->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Error listing directory");
        return 1;
    }

    return 0;
}