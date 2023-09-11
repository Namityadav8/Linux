#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    
    char ch;
    while (read(fd, &ch, 1) == 1) {
        if (write(STDOUT_FILENO, &ch, 1) != 1) {
            perror("write");
            close(fd);
            return 1;
        }
    }

   
    close(fd);

    return 0;
}