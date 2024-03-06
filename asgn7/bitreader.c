// Author: Debi Majumdar
// Filename: bitreader.c
// Assignment 7

#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a BitReader
struct BitReader {
    FILE *underlying_stream; // Pointer to the underlying file stream
    uint8_t byte; // Current byte being read
    uint8_t bit_position; // Current position of the bit being read in the byte
};

// Function to open a file for reading bits
BitReader *bit_read_open(const char *filename) {
    // Allocate memory for the BitReader structure
    BitReader *bit_reader = (BitReader *) malloc(sizeof(BitReader));
    if (bit_reader == NULL) {
        return NULL;
    }

    // Open the file for binary reading
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        free(bit_reader);
        return NULL;
    }

    // Initialize the BitReader structure
    bit_reader->underlying_stream = file;
    bit_reader->byte
        = 8; // Initialize byte to a value greater than 7 to trigger reading the first byte
    bit_reader->bit_position
        = 8; // Initialize bit position to a value greater than 7 to trigger reading the first byte

    return bit_reader;
}

// Function to close the BitReader and free memory
void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }
}

// Function to read a 32-bit unsigned integer from the BitReader
uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    for (int i = 0; i < 32; ++i) {
        word |= ((uint32_t) bit_read_bit(buf) << i);
    }
    return word;
}

// Function to read a 16-bit unsigned integer from the BitReader
uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    for (int i = 0; i < 16; ++i) {
        word |= (bit_read_bit(buf) << i);
    }
    return word;
}

// Function to read an 8-bit unsigned integer from the BitReader
uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (int i = 0; i < 8; ++i) {
        byte |= (bit_read_bit(buf) << i);
    }
    return byte;
}

// Function to read a single bit from the BitReader
uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int read_byte = fgetc(buf->underlying_stream);
        if (read_byte == EOF) {
            exit(EXIT_FAILURE);
        }
        buf->byte = (uint8_t) read_byte;
        buf->bit_position = 0;
    }

    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position += 1;

    return bit;
}
