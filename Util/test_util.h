// test_util.h
#pragma once
#include "logger.h"
#include "basic_types.h"


typedef enum {
    ASCII,
    BINARY,
    HEX,
    NUM
} LogFormat;


void log_test_summary(FILE *log_fd);
void log_value(FILE *log_fd, u64 value, LogFormat log_format);
void assert_equal_u64(u64 expected, u64 result, LogFormat log_format, u8 *file_name, u32 line_num);

#define LOG_VALUE_FORMAT(fd, x, log_format) fprintf(fd, "\t%s = ", #x); log_value(fd, x, log_format)

#define TEST_ASSERT_EQUAL_u64(expected, result, test_format) assert_equal_u64(expected, result, test_format, __FILE__, __LINE__)
#define TEST_SUMMARY(log_fd) log_test_summary(log_fd)
#define TEST_LOG_PASSED_TESTS (log_passed_tests = 1)

