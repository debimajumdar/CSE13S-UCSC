// Author: Debi Majumdar
// Filename: bitwriter.c
// Assignment 7

#include "bitwriter.h"

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a BitWriter
struct BitWriter {
    FILE *underlying_stream; // Pointer to the underlying file stream
    uint8_t byte; // Current byte being written
    uint8_t bit_position; // Current position of the bit being written in the byte
};

// Function to open a file for writing bits
BitWriter *bit_write_open(const char *filename) {
    // Allocate memory for the BitWriter structure
    BitWriter *bw = (BitWriter *) malloc(sizeof(BitWriter));
    if (bw == NULL) {
        return NULL;
    }

    // Open the file for binary writing
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        free(bw);
        return NULL;
    }

    // Initialize the BitWriter structure
    bw->underlying_stream = f;
    bw->byte = 0;
    bw->bit_position = 0;

    return bw;
}

// Function to close the BitWriter and write remaining bits to file
void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        // Write remaining bits if any
        if ((*pbuf)->bit_position > 0) {
            fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
        }

        // Close the file and free memory
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }
}

// Function to write a single bit to the BitWriter
void bit_write_bit(BitWriter *buf, uint8_t bit) {
    // Check if current byte is full
    if (buf->bit_position > 7) {
        // Write the current byte to the file and reset byte and bit position
        fputc(buf->byte, buf->underlying_stream);
        buf->byte = 0;
        buf->bit_position = 0;
    }

    // Write the bit to the current byte
    buf->byte |= (bit << buf->bit_position);
    buf->bit_position += 1;
}

// Function to write a 16-bit unsigned integer to the BitWriter
void bit_write_uint16(BitWriter *buf, uint16_t x) {
    // Write each bit of the 16-bit integer
    for (int i = 0; i < 16; ++i) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}

// Function to write a 32-bit unsigned integer to the BitWriter
void bit_write_uint32(BitWriter *buf, uint32_t x) {
    // Write each bit of the 32-bit integer
    for (int i = 0; i < 32; ++i) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}

// Function to write an 8-bit unsigned integer to the BitWriter
void bit_write_uint8(BitWriter *buf, uint8_t x) {
    // Write each bit of the 8-bit integer
    for (int i = 0; i < 8; ++i) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}
