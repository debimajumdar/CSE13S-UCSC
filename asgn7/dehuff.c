//Author: Debi Majumdar
//Asgn7
//Filename : dehuff.c

#include "bitreader.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

void dehuff_decompress_file(FILE *fout, BitReader *inbuf);

int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_filename = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_filename = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf(
                "Usage: dehuff -i infile -o outfile\n       dehuff -v -i infile -o outfile\n       "
                "dehuff -h\n");
            return 0;
        }
    }

    if (input_filename == NULL || output_filename == NULL) {
        fprintf(stderr, "Error: Input and output filenames are required.\n");
        return 1;
    }

    BitReader *input_buffer = bit_read_open(input_filename);
    if (input_buffer == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open output file
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        bit_read_close(&input_buffer);
        return 1;
    }

    dehuff_decompress_file(output_file, input_buffer);

    fclose(output_file);
    bit_read_close(&input_buffer);

    return 0;
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);

    assert(type1 == 'H');
    assert(type2 == 'C');

    uint16_t num_nodes = 2 * num_leaves - 1;

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
            node->right = stack[top--];
            node->left = stack[top--];
        }

        stack[++top] = node;
    }

    Node *code_tree = stack[top];

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

    node_free(&code_tree);
}
