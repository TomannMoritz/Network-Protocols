// bit util
#include "bit_util.h"

#include "test_util.c"


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
void log_data(FILE *log_fd, u8 *buffer, u32 num_bytes){
    fprintf(log_fd, "\n\nData:\n0b");
    log_bits(log_fd, buffer, num_bytes);
    fprintf(log_fd, "\n\n");
}


void log_bits(FILE *log_fd, u8 *buffer, u32 num_bytes){
    for (int i = 0; i < num_bytes; i++){
        fprintf(log_fd, BYTE_BIT_PATTERN " ", BYTE_BITS(buffer[i]));
    }
}


//--------------------------------------------------
u32 convert_32_bit_numbering(u32 value){
    u32 new_value = 0
        | (((value >> BYTE_SIZE * 0) & BYTE_MASK) << BYTE_SIZE * 3)
        | (((value >> BYTE_SIZE * 1) & BYTE_MASK) << BYTE_SIZE * 2)
        | (((value >> BYTE_SIZE * 2) & BYTE_MASK) << BYTE_SIZE * 1)
        | (((value >> BYTE_SIZE * 3) & BYTE_MASK) << BYTE_SIZE * 0);

    return new_value;
}


u64 convert_64_bit_numbering(u64 value){
    u64 new_value = 0
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
Optional_u64 create_n_bit_mask(u32 num_bits){
    Optional_u64 result = {};
    if (num_bits == 0){
        return result;
    }

    u32 max_bits = sizeof(u64) * BYTE_SIZE;
    u32 diff_bits = max_bits - num_bits;

    // NOTE: only mark invalid result
    u32 out_of_bounds = num_bits > max_bits;
    result.error.value |= out_of_bounds;

    u64 mask;
    mask = mask ^ (~mask);
    mask = mask >> diff_bits;

    result.value = mask;
    return result;
}


Optional_u64 extract_bits(DataOffset *data_offset, u32 num_bits){
    Optional_u64 result = {};
    u32 overflow_bytes = data_offset->offset_bits / BYTE_SIZE;

    // Update buffer pointer
    data_offset->data += overflow_bytes;
    data_offset->offset_bits -= overflow_bytes * BYTE_SIZE;

    // Check bounds: Check if all bits can be copied (valid copy)
    u32 out_of_bounds = data_offset->offset_bits + num_bits > sizeof(u64) * BYTE_SIZE;
    result.error.value |= out_of_bounds;
    OPTIONAL_ERROR_RETURN(result);

    // Copy next bytes
    u64 value = 0
        | (u64)data_offset->data[0] << (BYTE_SIZE * 7)
        | (u64)data_offset->data[1] << (BYTE_SIZE * 6)
        | (u64)data_offset->data[2] << (BYTE_SIZE * 5)
        | (u64)data_offset->data[3] << (BYTE_SIZE * 4)
        | (u64)data_offset->data[4] << (BYTE_SIZE * 3)
        | (u64)data_offset->data[5] << (BYTE_SIZE * 2)
        | (u64)data_offset->data[6] << (BYTE_SIZE * 1)
        | (u64)data_offset->data[7] << (BYTE_SIZE * 0);

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


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_convert_32_bit_numbering(){
    u32 result = convert_32_bit_numbering(0x0);
    TEST_ASSERT_EQUAL_u64(0x0, result, HEX);

    result = convert_32_bit_numbering(0xFFFFFFFF);
    TEST_ASSERT_EQUAL_u64(0xFFFFFFFF, result, HEX);

    result = convert_32_bit_numbering(0x2468ABEF);
    TEST_ASSERT_EQUAL_u64(0xEFAB6824, result, HEX);

    result = convert_32_bit_numbering(0xABCD);
    TEST_ASSERT_EQUAL_u64(0xCDAB0000, result, HEX);
}


void test_convert_64_bit_numbering(){
    u64 result = convert_64_bit_numbering(0x0);
    TEST_ASSERT_EQUAL_u64(0x0, result, HEX);

    result = convert_64_bit_numbering(0xFFFFFFFFFFFFFFFF);
    TEST_ASSERT_EQUAL_u64(0xFFFFFFFFFFFFFFFF, result, HEX);

    result = convert_64_bit_numbering(0x123456789ABCDEF);
    TEST_ASSERT_EQUAL_u64(0xEFCDAB8967452301, result, HEX);

    result = convert_64_bit_numbering(0xABCD);
    TEST_ASSERT_EQUAL_u64(0xCDAB000000000000, result, HEX);
}


void test_create_n_bit_mask(){
    Optional_u64 result = create_n_bit_mask(0);
    TEST_ASSERT_EQUAL_u64(result.error.value, 0, HEX);
    TEST_ASSERT_EQUAL_u64(result.value, 0, HEX);

    result = create_n_bit_mask(3);
    TEST_ASSERT_EQUAL_u64(result.error.value, 0, HEX);
    TEST_ASSERT_EQUAL_u64(result.value, 0b111, HEX);

    result = create_n_bit_mask(64);
    TEST_ASSERT_EQUAL_u64(result.error.value, 0, HEX);
    TEST_ASSERT_EQUAL_u64(result.value, 0xFFFFFFFFFFFFFFFF, HEX);

    result = create_n_bit_mask(65);
    TEST_ASSERT_EQUAL_u64(result.error.value & 0b1, 1, HEX);

    result = create_n_bit_mask(0xFFFFFFFF);
    TEST_ASSERT_EQUAL_u64(result.error.value & 0b1, 1, HEX);
}


void test_extract_bits(){
    // TODO:
}


void test_bit_util(){
    test_convert_32_bit_numbering();
    test_convert_64_bit_numbering();
    test_create_n_bit_mask();
    test_extract_bits();
}

