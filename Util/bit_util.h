// bit util
#pragma once
#include <stdio.h>

#define BYTE_SIZE 8
#define BYTE_MASK 0xFF


typedef struct {
    unsigned char *data;
    unsigned char offset_bits;
} DataOffset;


void print_bits(FILE *log_fd, unsigned char *buffer, int num_bytes);

unsigned int convert_32_bit_numbering(unsigned int value);
unsigned long int convert_64_bit_numbering(unsigned long int value);

unsigned long int create_n_bit_mask(int num_bits);
unsigned long int extract_bits(DataOffset *data_offset, int num_bits);
