// bit util
#include "bit_util.h"


#define ASCII_0 ('0')
#define ASCII_1 ('1')

#define BYTE_BIT_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_BITS(byte) \
    (byte & 0b10000000 ? ASCII_1 : ASCII_0), \
    (byte & 0b01000000 ? ASCII_1 : ASCII_0), \
    (byte & 0b00100000 ? ASCII_1 : ASCII_0), \
    (byte & 0b00010000 ? ASCII_1 : ASCII_0), \
    (byte & 0b00001000 ? ASCII_1 : ASCII_0), \
    (byte & 0b00000100 ? ASCII_1 : ASCII_0), \
    (byte & 0b00000010 ? ASCII_1 : ASCII_0), \
    (byte & 0b00000001 ? ASCII_1 : ASCII_0)


//--------------------------------------------------
void print_bits(FILE *log_fd, unsigned char *buffer, int num_bytes){
    fprintf(log_fd, "\n\nData:\n");
    for (int i = 0; i < num_bytes; i++){
        fprintf(log_fd, BYTE_BIT_PATTERN " ", BYTE_BITS(buffer[i]));
    }
    fprintf(log_fd, "\n\n");
}


//--------------------------------------------------
u32 convert_32_bit_numbering(unsigned int value){
    unsigned int new_value = 0
        | (((value >> BYTE_SIZE * 0) & BYTE_MASK) << BYTE_SIZE * 3)
        | (((value >> BYTE_SIZE * 1) & BYTE_MASK) << BYTE_SIZE * 2)
        | (((value >> BYTE_SIZE * 2) & BYTE_MASK) << BYTE_SIZE * 1)
        | (((value >> BYTE_SIZE * 3) & BYTE_MASK) << BYTE_SIZE * 0);

    return new_value;
}


u64 convert_64_bit_numbering(unsigned long int value){
    unsigned long int new_value = 0
        | (((value >> BYTE_SIZE * 0) & BYTE_MASK) << BYTE_SIZE * 7)
        | (((value >> BYTE_SIZE * 1) & BYTE_MASK) << BYTE_SIZE * 6)
        | (((value >> BYTE_SIZE * 2) & BYTE_MASK) << BYTE_SIZE * 5)
        | (((value >> BYTE_SIZE * 3) & BYTE_MASK) << BYTE_SIZE * 4)
        | (((value >> BYTE_SIZE * 4) & BYTE_MASK) << BYTE_SIZE * 3)
        | (((value >> BYTE_SIZE * 5) & BYTE_MASK) << BYTE_SIZE * 2)
        | (((value >> BYTE_SIZE * 6) & BYTE_MASK) << BYTE_SIZE * 1)
        | (((value >> BYTE_SIZE * 7) & BYTE_MASK) << BYTE_SIZE * 0);

    return new_value;
}


//--------------------------------------------------
Optional_u64 create_n_bit_mask(int num_bits){
    Optional_u64 result = {};

    int max_bits = sizeof(long int) * BYTE_SIZE;
    int diff_bits = max_bits - num_bits;

    // NOTE: only mark invalid result
    int out_of_bounds = num_bits > max_bits;
    result.error.value |= out_of_bounds;

    unsigned long int mask;
    mask = mask ^ (~mask);
    mask = mask >> diff_bits;

    result.value = mask;
    return result;
}


Optional_u64 extract_bits(DataOffset *data_offset, int num_bits){
    Optional_u64 result = {};
    int overflow_bytes = data_offset->offset_bits / BYTE_SIZE;

    // Update buffer pointer
    data_offset->data += overflow_bytes;
    data_offset->offset_bits -= overflow_bytes * BYTE_SIZE;

    // Check bounds: Check if all bits can be copied (valid copy)
    int out_of_bounds = data_offset->offset_bits + num_bits > sizeof(long int) * BYTE_SIZE;
    result.error.value |= out_of_bounds;
    OPTIONAL_ERROR_RETURN(result);

    // Copy next bytes
    unsigned long int value = 0
        | (unsigned long int)data_offset->data[0] << (BYTE_SIZE * 7)
        | (unsigned long int)data_offset->data[1] << (BYTE_SIZE * 6)
        | (unsigned long int)data_offset->data[2] << (BYTE_SIZE * 5)
        | (unsigned long int)data_offset->data[3] << (BYTE_SIZE * 4)
        | (unsigned long int)data_offset->data[4] << (BYTE_SIZE * 3)
        | (unsigned long int)data_offset->data[5] << (BYTE_SIZE * 2)
        | (unsigned long int)data_offset->data[6] << (BYTE_SIZE * 1)
        | (unsigned long int)data_offset->data[7] << (BYTE_SIZE * 0);

    // Clear next bits
    value = value >> (64 - num_bits - data_offset->offset_bits);

    // Clear offset bits
    Optional_u64 mask = create_n_bit_mask(num_bits);
    result.error.value |= mask.error.value;
    OPTIONAL_ERROR_RETURN(result);

    value &= mask.value;

    // Update buffer offset
    data_offset->offset_bits += num_bits;
    result.value = value;
    return result;
}

