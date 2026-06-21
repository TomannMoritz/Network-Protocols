// bit util
#pragma once
#include <stdio.h>

#define BYTE_SIZE 8
#define BYTE_MASK 0xFF

#define BIT_MASK_01 0b1
#define BIT_MASK_02 0b11
#define BIT_MASK_03 0b111
#define BIT_MASK_04 0xF
#define BIT_MASK_05 0b11111
#define BIT_MASK_06 0b111111
#define BIT_MASK_07 0b1111111
#define BIT_MASK_08 0xFF


typedef struct {
    unsigned char *data;
    unsigned char offset_bits;
} DataOffset;


void print_bits(FILE *log_fd, unsigned char *buffer, int num_bytes);

unsigned int convert_32_bit_numbering(unsigned int value);
unsigned long int convert_64_bit_numbering(unsigned long int value);

unsigned long int create_n_bit_mask(int num_bits);
unsigned long int extract_bits(DataOffset *data_offset, int num_bits);
