// 4-BasicTransportProtocl

#include "basic_transport_protocol.h"


void parse_btp_a(BTP_A *btp_a, DataOffset *data_offset){
    btp_a->destination_port = extract_bits(data_offset, BTP_A_DESTINATION_PORT_BITS).value;
    btp_a->source_port = extract_bits(data_offset, BTP_A_SOURCE_PORT_BITS).value;
}


void parse_btp_b(BTP_B *btp_b, DataOffset *data_offset){
    btp_b->destination_port = extract_bits(data_offset, BTP_B_DESTINATION_PORT_BITS).value;
    btp_b->destination_port_info = extract_bits(data_offset, BTP_B_DESTINATION_PORT_INFO_BITS).value;
}


//--------------------------------------------------
// Testing
//--------------------------------------------------

//--------------------------------------------------
void test_basic_transport_protocol(){
    // TODO:
    TEST_ASSERT_EQUAL_u64(0, 4, NUM);
}
