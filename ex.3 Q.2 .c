#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buffer[4096]; 
    char filename[] = "output.txt";
    int file_descriptor;

   
    file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (file_descriptor == -1) {
        perror("Error opening file");
        exit(1);
    }

    printf("Enter text (type '$' to stop):\n");

    while (1) {
        ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));

        if (bytes_read == -1) {
            perror("Error reading from console");
            exit(1);
        }

       
        ssize_t bytes_written = write(file_descriptor, buffer, bytes_read);

        if (bytes_written == -1) {
            perror("Error writing to file");
            exit(1);
        }

       
        if (bytes_read > 0 && buffer[0] == '$') {
            break;
        }
    }

    if (close(file_descriptor) == -1) {
        perror("Error closing file");
        exit(1);
    }

    printf("Input has been written to %s.\n", filename);

    return 0;
}