//File Name: xd.c
//Author Name: Debi Majumdar

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16

// Function to display hexadecimal and ASCII representation of data
void display_hex_ascii(unsigned char *data, size_t length) {
    size_t index;

    // Prining the hex values
    for (index = 0; index < length; ++index) {
        printf("%02x", data[index]);
        if (index % 2 != 0) {
            printf(" ");
        }
    }

    // Padding spaces here
    for (; index < BUFFER_SIZE; ++index) {
        if (index % 2 != 0) {
            printf(" ");
        }
        printf("  ");
    }

    // ASCII representation
    printf(" ");
    for (index = 0; index < length; ++index) {
        if (data[index] >= 32 && data[index] <= 126) {
            printf("%c", data[index]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int fd;

    // Check if a filename is provided as an argument here
    if (argc != 2 && argc != 1) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(1);
    }

    // Open the file or use stdin if no filename provided!
    fd = (argc == 2) ? open(argv[1], O_RDONLY) : STDIN_FILENO;
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    unsigned char buf[BUFFER_SIZE];
    ssize_t bytes_read;
    ssize_t current_byte = 0;

    // Read data from file and display hexadecimal and ASCII representation
    while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0) {
        // Printing the formatted output

        if (fd == STDIN_FILENO) {
            while (bytes_read < BUFFER_SIZE) {
                ssize_t remaining_bytes;
                remaining_bytes
                    = read(fd, buf + bytes_read, BUFFER_SIZE - (unsigned long) bytes_read);
                if (remaining_bytes > 0) {
                    bytes_read += remaining_bytes;
                } else if (remaining_bytes == 0) { // EOF reached
                    break;
                } else {
                    exit(0);
                }
            }

            printf("%08lx: ", (unsigned long) current_byte);
            display_hex_ascii(buf, (size_t) bytes_read);
            current_byte += bytes_read;
        } else {
            printf("%08lx: ", (unsigned long) current_byte);

            display_hex_ascii(buf, (size_t) bytes_read);

            current_byte += bytes_read;

            if (bytes_read < BUFFER_SIZE) {
                break; // Exit loop if less than buffer size read, for throttle or whatever
            }
        }
    }

    // Close the file if it was opened
    if (fd != STDIN_FILENO) {
        close(fd);
    }

    return 0;
}
