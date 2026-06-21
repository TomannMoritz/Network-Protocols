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
unsigned int convert_32_bit_numbering(unsigned int value){
    unsigned int new_value = 0 +
        ((unsigned int)((unsigned int)(value >> BYTE_SIZE* 0) & BYTE_MASK) << BYTE_SIZE* 3) +
        ((unsigned int)((unsigned int)(value >> BYTE_SIZE* 1) & BYTE_MASK) << BYTE_SIZE* 2) +
        ((unsigned int)((unsigned int)(value >> BYTE_SIZE* 2) & BYTE_MASK) << BYTE_SIZE* 1) +
        ((unsigned int)((unsigned int)(value >> BYTE_SIZE* 3) & BYTE_MASK) << BYTE_SIZE* 0);

    return new_value;
}


unsigned long int convert_64_bit_numbering(unsigned long int value){
    unsigned long int new_value = 0 +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 0) & BYTE_MASK) << BYTE_SIZE* 7) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 1) & BYTE_MASK) << BYTE_SIZE* 6) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 2) & BYTE_MASK) << BYTE_SIZE* 5) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 3) & BYTE_MASK) << BYTE_SIZE* 4) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 4) & BYTE_MASK) << BYTE_SIZE* 3) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 5) & BYTE_MASK) << BYTE_SIZE* 2) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 6) & BYTE_MASK) << BYTE_SIZE* 1) +
        ((unsigned long int)((unsigned long int)(value >> BYTE_SIZE* 7) & BYTE_MASK) << BYTE_SIZE* 0);

    return new_value;
}


//--------------------------------------------------
unsigned long int create_n_bit_mask(int num_bits){
    unsigned long int mask = 0b1;
    mask = (mask << num_bits) - 1;
    return mask;
}


unsigned long int extract_bits(DataOffset *data_offset, int num_bits){
    int overflow_bytes = data_offset->offset_bits / BYTE_SIZE;

    // Update buffer pointer
    data_offset->data += overflow_bytes;
    data_offset->offset_bits -= overflow_bytes * BYTE_SIZE;

    // Check bounds: Check if all bits can be copied (valid copy)
    int out_of_bounds = data_offset->offset_bits + num_bits > sizeof(long int);
    if (out_of_bounds){
        return 0;
    }

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
    unsigned long int mask = create_n_bit_mask(num_bits);
    value &= mask;

    // Update buffer offset
    data_offset->offset_bits += num_bits;
    return value;
}

