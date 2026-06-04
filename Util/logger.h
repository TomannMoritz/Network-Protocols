#pragma once
#include <stdio.h>
#include <ctype.h>

#define LOG_VALUE(fd, x) fprintf(fd, "\t%s = %04lx\n", #x, x)
#define LOG_STR_VALUE(fd, x, str) fprintf(fd, "\t%s = %s\n", #x, str)

#define BYTE_SIZE 8

// NOTE: A MAC Address requires 6 BYTES as a number
// Converting to a string requires more memory:
//  Each BYTE is displayed as two HEX values (each value requires its own BYTE => 12 BYTES)
//  Additionally each SEPARATOR requires one BYTE => 5 BYTES
// => MIN 17 BYTES in total
#define ADDR_SPACE_STR (BYTE_SIZE * 3)

unsigned long int convert_address_bit_numbering(unsigned long int address);
void format_mac_address(unsigned long int address, char *buf);
void log_byte_data(FILE *log_fd, unsigned char *data, int data_size, int line_size);

