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
// Logging
//--------------------------------------------------
void log_btp_a(FILE *log_fd, BTP_A *btp_a, LogFormat log_format){
    LOG_VALUE_FORMAT(log_fd, btp_a->destination_port, log_format);
    LOG_VALUE_FORMAT(log_fd, btp_a->source_port, log_format);
}

void log_btp_b(FILE *log_fd, BTP_B *btp_b, LogFormat log_format){
    LOG_VALUE_FORMAT(log_fd, btp_b->destination_port, log_format);
    LOG_VALUE_FORMAT(log_fd, btp_b->destination_port_info, log_format);
}


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_parse_btp_a(){
    u8 data[] = { 0xAB, 0xCD, 0x45, 0x67};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    BTP_A btp_a;

    parse_btp_a(&btp_a, &test_offset);

    TEST_ASSERT_EQUAL_u64(0xABCD, btp_a.destination_port, HEX);
    TEST_ASSERT_EQUAL_u64(0x4567, btp_a.source_port, HEX);
}


void test_parse_btp_b(){
    u8 data[] = { 0xAB, 0xCD, 0x45, 0x67};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    BTP_B btp_b;

    parse_btp_b(&btp_b, &test_offset);

    TEST_ASSERT_EQUAL_u64(0xABCD, btp_b.destination_port, HEX);
    TEST_ASSERT_EQUAL_u64(0x4567, btp_b.destination_port_info, HEX);
}


//--------------------------------------------------
void test_basic_transport_protocol(){
    test_parse_btp_a();
    test_parse_btp_b();
}
