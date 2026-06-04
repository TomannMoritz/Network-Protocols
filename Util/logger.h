#pragma once
#include <stdio.h>
#include <ctype.h>

#define LOG_VALUE(fd, x) fprintf(fd, "\t%s = %lx\n", #x, x)

void log_byte_data(FILE *log_fd, unsigned char *data, int data_size, int line_size);

