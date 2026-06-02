#include "logger.h"

#define HEX_FORMAT "%02X "
#define HEX_FORMAT_OFFSET 3
#define UNPRINTABLE_CHAR '.'
#define SPACE_CHAR ' '


void log_byte_data(FILE *log_fd, void *data, int data_size, int line_size){
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

        sprintf(hex_buff + offset * HEX_FORMAT_OFFSET, HEX_FORMAT, *p);
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
