// Testing
#include "Util/bit_util.h"
#include "Util/bit_util.c"

// NOTE: Call all module test functions
int main(){
    // TEST_LOG_PASSED_TESTS;
    test_bit_util();

    TEST_SUMMARY(stdout);
    return 0;
}
