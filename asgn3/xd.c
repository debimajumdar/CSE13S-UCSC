#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16

void print_hex_ascii(unsigned char *buffer, size_t size) {
    size_t i;

    //print hex values
    for (i = 0; i < size; ++i) {
        printf("%02x", buffer[i]);
        if (i % 2 != 0) {
            printf(" ");
        }
    }

    //padding spaces
    for (; i < BUFFER_SIZE; ++i) {
        if (i % 2 != 0) {
            printf(" ");
        }
        printf("  ");
    }

    //ascii representation
    printf(" ");
    for (i = 0; i < size; ++i) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int file_descriptor;

    //check if a filename is provided as a argument
    if (argc == 2) {
        //open file
        file_descriptor = open(argv[1], O_READ);

        if (file_descriptor == -1) {
            exit(1);
        }
    } else if (argc == 1) {
        //use stdin if no filename provided
        file_descriptor = STDIN_FILENO;
    } else {
        exit(1);
    }

    unsigned char buffer[BUFFER_SIZE];
    ssize_t bytesRead; //change size_t to ssize_t for bytesRead

    ssize_t curr_byte = 0;

    while ((bytesRead = read(file_descriptor, buffer, BUFFER_SIZE)) > 0) {
        //print the formatted output

        if (file_descriptor == STDIN_FILENO) {
            while (bytesRead < BUFFER_SIZE) {
                ssize_t remainingBytes;
                remainingBytes = read(
                    file_descriptor, buffer + bytesRead, BUFFER_SIZE - (unsigned long) bytesRead);
                if (remainingBytes > 0) {
                    bytesRead += remainingBytes;
                } else if (remainingBytes == 0) { //eof reached
                    break;
                } else {
                    exit(0);
                }
            }

            printf("%08lx: ", (unsigned long) curr_byte);
            print_hex_ascii(buffer, (size_t) bytesRead);
            curr_byte += bytesRead;
        } else {
            printf("%08lx: ", (unsigned long) curr_byte);

            print_hex_ascii(buffer, (size_t) bytesRead);

            curr_byte += bytesRead;

            if (bytesRead < BUFFER_SIZE) {
                break; //exit loop if less than buffer size read, for throttled input
            }
        }
    }

    //close the file if it was opened
    if (file_descriptor != STDIN_FILENO) {
        close(file_descriptor);
    }

    return 0;
}
