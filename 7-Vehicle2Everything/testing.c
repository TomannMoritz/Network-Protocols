// Testing

#include "../Util/bit_util.h"

#include "../1-IEEE-1609.2/ieee_1609_dot_2.h"
#include "../1-IEEE-802.11/ieee_802_11.h"
#include "../2-LogicalLinkControl/logical_link_control.h"
#include "../3-GeoNetworking/its_geonetworking.h"
#include "../4-BasicTransportProtocol/basic_transport_protocol.h"
#include "../7-IntelligentTransportSystem/its_messages.h"


// NOTE: Call all module test functions
int main(){
    // TEST_LOG_PASSED_TESTS;
    test_bit_util();

    test_ieee_1609_dot_2();
    test_ieee_802_dot_11();
    test_logical_link_control();
    test_geonetworking();
    test_basic_transport_protocol();
    test_its_messages();

    TEST_SUMMARY(stdout);
    return 0;
}
