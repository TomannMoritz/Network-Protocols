#include "logger.h"

#define HEX_FORMAT "%02X"
#define HEX_SPACE " "
#define HEX_FORMAT_OFFSET 3

#define UNPRINTABLE_CHAR '.'
#define SPACE_CHAR ' '

#define BYTE_MASK 0xFF
#define MAC_SEPARATOR ":"
#define MAC_FMT HEX_FORMAT MAC_SEPARATOR
#define MAC_ADDRESS_FORMAT MAC_FMT MAC_FMT MAC_FMT MAC_FMT MAC_FMT HEX_FORMAT


unsigned long int convert_address_bit_numbering(unsigned long int address){
    unsigned long int new_addr = 0 +
        ((unsigned long int)((address >> BYTE_SIZE* 0) & BYTE_MASK) << BYTE_SIZE* 5) +
        ((unsigned long int)((address >> BYTE_SIZE* 1) & BYTE_MASK) << BYTE_SIZE* 4) +
        ((unsigned long int)((address >> BYTE_SIZE* 2) & BYTE_MASK) << BYTE_SIZE* 3) +
        ((unsigned long int)((address >> BYTE_SIZE* 3) & BYTE_MASK) << BYTE_SIZE* 2) +
        ((unsigned long int)((address >> BYTE_SIZE* 4) & BYTE_MASK) << BYTE_SIZE* 1) +
        ((unsigned long int)((address >> BYTE_SIZE* 5) & BYTE_MASK) << BYTE_SIZE* 0);

    return new_addr;
}


void format_mac_address(unsigned long int address, char *buf){
    sprintf(buf, MAC_ADDRESS_FORMAT,
            (unsigned int)(address >> BYTE_SIZE * 5) & BYTE_MASK,
            (unsigned int)(address >> BYTE_SIZE * 4) & BYTE_MASK,
            (unsigned int)(address >> BYTE_SIZE * 3) & BYTE_MASK,
            (unsigned int)(address >> BYTE_SIZE * 2) & BYTE_MASK,
            (unsigned int)(address >> BYTE_SIZE * 1) & BYTE_MASK,
            (unsigned int)(address >> BYTE_SIZE * 0)& BYTE_MASK
           );
}


void log_byte_data(FILE *log_fd, unsigned char *data, int data_size, int line_size){
    unsigned char *p = data;
    char hex_buff[line_size * 4] = {};
    char char_buff[line_size * 2] = {};

    const char *DATA_FORMAT = "\n\t\t%s%s\t%s";

    int offset;
    for (int i = 0; i < data_size; i++, p++){
        offset = i % line_size;

        if (offset == 0){
            fprintf(log_fd, DATA_FORMAT, hex_buff, "", char_buff);
        }

        sprintf(hex_buff + offset * HEX_FORMAT_OFFSET, HEX_FORMAT HEX_SPACE, *p);
        sprintf(char_buff + offset, "%c", isprint(*p) ? *p: UNPRINTABLE_CHAR);
    }

    // add last line spacing
    char space[line_size * HEX_FORMAT_OFFSET] = {};
    int space_to_fill = (line_size - offset) * HEX_FORMAT_OFFSET;
    for (int i = 0; i < space_to_fill; i++){
        space[i] = SPACE_CHAR;
    }
    fprintf(log_fd, DATA_FORMAT, hex_buff, space, char_buff);
    fprintf(log_fd, "\n");
}
