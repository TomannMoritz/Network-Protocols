// test_util.c
#include "test_util.h"


#define EXPECTED_STR "\n\tExpected: \t"
#define RESULT_STR   "\tResult:   \t"

#define TEST_INFO "%s(%s:%d) "
const u8 *TEST_PASS = "[~] PASS ";
const u8 *TEST_FAIL = "[!] FAIL ";


u8 log_passed_tests = 0;
u64 tests_passed = 0;
u64 tests_failed = 0;


void log_test_summary(FILE *log_fd){
    u64 tests_total = tests_passed + tests_failed;
    fprintf(log_fd, "-------------------------\n");
    fprintf(log_fd, "Tests: %lu\n", tests_total);
    fprintf(log_fd, " - Passed: %lu\n", tests_passed);
    fprintf(log_fd, " - Failed: %lu\n", tests_failed);
}


void log_test_result(FILE *log_fd, const u8 *result, u8 *file_name, u32 line_num){
    fprintf(log_fd, TEST_INFO, result, file_name, line_num);
}


void log_u64_ascii(FILE *log_fd, u64 *value){
    u8 *ptr = (u8 *)value;

    for (int i = BYTE_SIZE - 1; i >= 0; i--){
        fprintf(log_fd, "%c", ptr[i]);
    }
}


void log_u64_binary(FILE *log_fd, u64 *value){
    u8 *ptr = (u8 *)value;
    fprintf(log_fd, "0b");

    for (int i = BYTE_SIZE - 1; i >= 0; i--){
        log_bits(log_fd, (ptr + i), 1);
    }
}



//--------------------------------------------------
void log_value(FILE *log_fd, u64 value, LogFormat log_format){
    switch (log_format){
        case ASCII:
            fprintf(log_fd, "'");
            log_u64_ascii(log_fd, &value);
            fprintf(log_fd, "'");
            break;

        case BINARY:
            log_u64_binary(log_fd, &value);
            break;

        case HEX:
            fprintf(log_fd, "0x%lX", value);
            break;

        case NUM:
        default:
            fprintf(log_fd, "%lu", value);
            break;
    }

    fprintf(log_fd, "\n");
}


void assert_equal_u64(u64 expected, u64 result, LogFormat log_format, u8 *file_name, u32 line_num){
    if (expected == result){
        tests_passed++;

        if (log_passed_tests){
            log_test_result(stdout, TEST_PASS, file_name, line_num);
            fprintf(stdout, "\n");
        }
        return;
    }

    tests_failed++;

    log_test_result(stdout, TEST_FAIL, file_name, line_num);
    fprintf(stdout, EXPECTED_STR);
    u64 *expected_p = &expected;
    u64 *result_p = &result;


    log_value(stdout, *expected_p, log_format);
    fprintf(stdout, RESULT_STR);
    log_value(stdout, *result_p, log_format);
    fprintf(stdout, "\n");
}

