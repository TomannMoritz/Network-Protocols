// bit util
#pragma once
#include <stdio.h>
#include "basic_types.h"

#define BYTE_SIZE 8
#define BYTE_MASK 0xFF


typedef struct {
    unsigned char *data;
    unsigned char offset_bits;
} DataOffset;


void print_bits(FILE *log_fd, unsigned char *buffer, int num_bytes);

unsigned int convert_32_bit_numbering(unsigned int value);
unsigned long int convert_64_bit_numbering(unsigned long int value);

Optional_u64 create_n_bit_mask(int num_bits);
Optional_u64 extract_bits(DataOffset *data_offset, int num_bits);

