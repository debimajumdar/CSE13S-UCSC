//Author: Debi Majumdar
//Filename: dehuff.c
//Asgn7

#include "bitreader.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold a Huffman code and its length
typedef struct Code {
    uint64_t code; // The Huffman code
    uint8_t code_length; // Length of the code in bits
} Code;

// Function prototypes
void dehuff_decompress_file(FILE *fout, BitReader *inbuf);

int main(int argc, char *argv[]) {
    // Initialize filenames as NULL to check for their assignment later
    char *input_filename = NULL;
    char *output_filename = NULL;

    // Parse command line arguments to extract input and output filenames
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_filename = argv[i + 1];
            i++; // Skip next argument since it's already processed
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_filename = argv[i + 1];
            i++; // Skip next argument since it's already processed
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("Usage: dehuff -i infile -o outfile\n");
            return 0; // Exit if help is requested
        }
    }

    // Validate that both input and output filenames have been provided
    if (input_filename == NULL || output_filename == NULL) {
        fprintf(stderr, "Error: Input and output filenames are required.\n");
        return 1; // Exit with error code
    }

    // Open input file for reading
    BitReader *input_buffer = bit_read_open(input_filename);
    if (input_buffer == NULL) {
        perror("Error opening input file");
        return 1; // Exit with error code if file cannot be opened
    }

    // Open output file for writing
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        bit_read_close(&input_buffer); // Clean up input buffer before exiting
        return 1;
    }

    // Decompress the input file into the output file
    dehuff_decompress_file(output_file, input_buffer);

    // Clean up: close files and release resources
    fclose(output_file);
    bit_read_close(&input_buffer);

    return 0; // Successful completion
}

// Function to decompress a Huffman-encoded file
void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);

    assert(type1 == 'H' && type2 == 'C');

    uint16_t num_leaves = bit_read_uint16(inbuf);
    //Explicitly cast the result to uint16_t
    uint16_t num_nodes = (uint16_t) (2 * num_leaves - 1);

    Node *stack[64];
    int top = -1;

    for (uint16_t i = 0; i < num_nodes; ++i) {
        int bit = bit_read_bit(inbuf);
        Node *node;

        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack[top];
            stack[top] = NULL; // Ensure the node is removed
            top--;
            node->left = stack[top];
            stack[top] = NULL; // Ensure the node is removed
            top--;
        }

        stack[++top] = node;
    }

    Node *code_tree = stack[top];
    stack[top] = NULL; // Ensure the node is removed
    top--;

    // Ensure the loop is properly closed with its brace
    for (uint32_t i = 0; i < filesize; ++i) {
        Node *node = code_tree;

        while (1) {
            int bit = bit_read_bit(inbuf);

            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }

            if (node->left == NULL && node->right == NULL) {
                fwrite(&(node->symbol), sizeof(uint8_t), 1, fout);
                break;
            }
        }
    }

    // Ensure the function is properly closed with its brace
    node_free(&code_tree);
}
