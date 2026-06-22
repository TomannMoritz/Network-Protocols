// test_util.h
#pragma once
#include "logger.h"
#include "basic_types.h"


typedef enum {
    ASCII,
    BINARY,
    HEX,
    NUM
} TestLogFormat;


void log_test_summary(FILE *log_fd);
void assert_equal_u64(u64 expected, u64 result, TestLogFormat test_log_format, u8 *file_name, u32 line_num);

#define TEST_ASSERT_EQUAL_u64(expected, result, test_format) assert_equal_u64(expected, result, test_format, __FILE__, __LINE__)
#define TEST_SUMMARY(log_fd) log_test_summary(log_fd)
#define TEST_LOG_PASSED_TESTS (log_passed_tests = 1)

