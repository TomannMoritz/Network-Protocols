// Testing

#include "Util/bit_util.h"

#include "3-GeoNetworking/its_geonetworking.h"
#include "3-GeoNetworking/its_geonetworking.c"

#include "7-IntelligentTransportSystem/its_messages.h"
#include "7-IntelligentTransportSystem/its_messages.c"


// NOTE: Call all module test functions
int main(){
    // TEST_LOG_PASSED_TESTS;
    test_bit_util();

    test_geonetworking();
    test_its_messages();

    TEST_SUMMARY(stdout);
    return 0;
}
