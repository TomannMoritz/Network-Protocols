// bit util
#pragma once
#include <stdio.h>
#include "basic_types.h"
#include "test_util.h"

#define BYTE_SIZE 8
#define BYTE_MASK 0xFF


typedef struct {
    unsigned char *data;
    unsigned char offset_bits;
} DataOffset;


void log_data(FILE *log_fd, u8 *buffer, u32 num_bytes);
void log_bits(FILE *log_fd, u8 *buffer, u32 num_bytes);

u32 convert_32_bit_numbering(u32 value);
u64 convert_64_bit_numbering(u64 value);

Optional_u64 create_n_bit_mask(u32 num_bits);
Optional_u64 extract_bits(DataOffset *data_offset, u32 num_bits);

//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_bit_util();
