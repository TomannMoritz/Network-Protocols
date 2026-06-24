// GeoNetworking
#include "its_geonetworking.h"


//--------------------------------------------------
void parse_life_time(LifeTime *life_time, DataOffset *data_offset){
    life_time->multiplier = extract_bits(data_offset, LIFETIME_MULTIPLIER_BITS).value;
    life_time->base = extract_bits(data_offset, LIFETIME_BASE_BITS).value;
}


void parse_basic_header(BasicHeader *basic_header, DataOffset *data_offset){
    basic_header->version = extract_bits(data_offset, BASIC_VERSION_BITS).value;
    basic_header->next_header = extract_bits(data_offset, BASIC_NEXT_HEADER_BITS).value;

    data_offset->offset_bits += BASIC_RESERVED_BITS;
    parse_life_time(&basic_header->life_time, data_offset);
    basic_header->rhl = extract_bits(data_offset, BASIC_RHL_BITS).value;
}


//--------------------------------------------------
void parse_common_flags(CommonFlags *common_flags, DataOffset *data_offset){
    common_flags->mobile = extract_bits(data_offset, COMMON_FLAG_MOBILE_BITS).value;
    data_offset->offset_bits += COMMON_FLAG_RESERVED_BITS;
}


void parse_common_header(CommonHeader *common_header, DataOffset *data_offset){
    common_header->next_header = extract_bits(data_offset, COMMON_NEXT_HEADER_BITS).value;
    data_offset->offset_bits += COMMON_RESERVED_BITS_1;

    common_header->header_type = extract_bits(data_offset, COMMON_HEADER_TYPE_BITS).value;
    common_header->header_sub_type = extract_bits(data_offset, COMMON_HEADER_SUB_TYPE_BITS).value;

    common_header->traffic_class = extract_bits(data_offset, COMMON_TRAFFIC_CLASS_BITS).value;
    parse_common_flags(&common_header->common_flags, data_offset);
    common_header->payload_length = extract_bits(data_offset, COMMON_PAYLOAD_LENGTH_BITS).value;

    common_header->mhl = extract_bits(data_offset, COMMON_MHL_BITS).value;
    data_offset->offset_bits += COMMON_RESERVED_BITS_2;
}


//--------------------------------------------------
void parse_gn_addr(GN_ADDR *gn_addr, DataOffset *data_offset){
    gn_addr->manual = extract_bits(data_offset, GN_ADDR_MANUAL_BITS).value;
    gn_addr->station_type = extract_bits(data_offset, GN_ADDR_STATION_TYPE_BITS).value;

    data_offset->offset_bits += GN_ADDR_RESERVED_BITS;
    gn_addr->mid = extract_bits(data_offset, GN_ADDR_MID_BITS).value;
}


void parse_long_position_vector(LongPositionVector *lpv, DataOffset *data_offset){
    parse_gn_addr(&lpv->gn_addr, data_offset);

    lpv->tst = extract_bits(data_offset, LPV_TST_BITS).value;
    lpv->latitude = extract_bits(data_offset, LPV_LATITUDE_BITS).value;
    lpv->longitude = extract_bits(data_offset, LPV_LONGITUDE_BITS).value;
    lpv->pai = extract_bits(data_offset, LPV_PAI_BITS).value;
    lpv->speed = extract_bits(data_offset, LPV_SPEED_BITS).value;
    lpv->heading = extract_bits(data_offset, LPV_HEADING_BITS).value;
}


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_parse_life_time(){
    u8 data[] = {0xFF, 0b10000100, 0b01111010};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    LifeTime life_time = {};

    parse_life_time(&life_time, &test_offset);
    TEST_ASSERT_EQUAL_u64(0b111111, life_time.multiplier, BINARY);
    TEST_ASSERT_EQUAL_u64(0b11, life_time.base, BINARY);

    parse_life_time(&life_time, &test_offset);
    TEST_ASSERT_EQUAL_u64(0b100001, life_time.multiplier, BINARY);
    TEST_ASSERT_EQUAL_u64(0b00, life_time.base, BINARY);

    parse_life_time(&life_time, &test_offset);
    TEST_ASSERT_EQUAL_u64(0b011110, life_time.multiplier, BINARY);
    TEST_ASSERT_EQUAL_u64(0b10, life_time.base, BINARY);

    extract_bits(&test_offset, 0);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.offset_bits, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.length, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.error.value, HEX);
}


void test_parse_basic_header(){
    u8 data[] = {0xAB, 0xFF, 0xFF, 0x78};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    BasicHeader basic_header = {};

    parse_basic_header(&basic_header, &test_offset);
    TEST_ASSERT_EQUAL_u64(0xA, basic_header.version, HEX);
    TEST_ASSERT_EQUAL_u64(0xB, basic_header.next_header, HEX);
    TEST_ASSERT_EQUAL_u64(0x78, basic_header.rhl, HEX);

    extract_bits(&test_offset, 0);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.offset_bits, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.length, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.error.value, HEX);
}


//--------------------------------------------------
void test_parse_common_flags(){
    u8 data[] = {0x80, 0x7F};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    CommonFlags common_flags = {};

    parse_common_flags(&common_flags, &test_offset);
    TEST_ASSERT_EQUAL_u64(0x1, common_flags.mobile, BINARY);

    parse_common_flags(&common_flags, &test_offset);
    TEST_ASSERT_EQUAL_u64(0x0, common_flags.mobile, BINARY);

    extract_bits(&test_offset, 0);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.offset_bits, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.length, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.error.value, HEX);
}


void test_parse_common_header(){
    u8 data[] = {0xAB, 0xCD, 0x89, 0xFF, 0x34, 0x56, 0x10, 0xFF};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    CommonHeader common_header = {};

    parse_common_header(&common_header, &test_offset);
    TEST_ASSERT_EQUAL_u64(0xA, common_header.next_header, HEX);
    TEST_ASSERT_EQUAL_u64(0xC, common_header.header_type, HEX);
    TEST_ASSERT_EQUAL_u64(0xD, common_header.header_sub_type, HEX);
    TEST_ASSERT_EQUAL_u64(0x89, common_header.traffic_class, HEX);

    TEST_ASSERT_EQUAL_u64(0x1, common_header.common_flags.mobile, HEX);

    TEST_ASSERT_EQUAL_u64(0x3456, common_header.payload_length, HEX);
    TEST_ASSERT_EQUAL_u64(0x10, common_header.mhl, HEX);

    extract_bits(&test_offset, 0);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.offset_bits, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.length, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.error.value, HEX);
}


//--------------------------------------------------
void test_parse_gn_addr(){
    u8 data[] = {0b11000000, 0xFF, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE};
    DataOffset test_offset = create_data_offset(data, sizeof(data));
    GN_ADDR gn_addr = {};

    parse_gn_addr(&gn_addr, &test_offset);

    TEST_ASSERT_EQUAL_u64(0b1, gn_addr.manual, BINARY);
    TEST_ASSERT_EQUAL_u64(0b10000, gn_addr.station_type, BINARY);
    TEST_ASSERT_EQUAL_u64(0x3456789ABCDE, gn_addr.mid, HEX);

    extract_bits(&test_offset, 0);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.offset_bits, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.length, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.error.value, HEX);
}


void test_parse_long_position_vector(){
    u8 data[] = {
        0xFF, 0xFF, 0xED, 0xEC, 0xEB, 0xEA, 0xE0, 0xE9,
        0xAA, 0xBB, 0xCC, 0xDD,
        0xBA, 0xBB, 0xBC, 0xBD,
        0xCA, 0xCB, 0xCC, 0xCD,
        0b11010000, 0b10011001,
        0x67, 0x67
    };

    DataOffset test_offset = create_data_offset(data, sizeof(data));
    LongPositionVector lpv = {};

    parse_long_position_vector(&lpv, &test_offset);

    // GN_ADDR
    TEST_ASSERT_EQUAL_u64(0b1, lpv.gn_addr.manual, BINARY);
    TEST_ASSERT_EQUAL_u64(0b11111, lpv.gn_addr.station_type, BINARY);
    TEST_ASSERT_EQUAL_u64(0xEDECEBEAE0E9, lpv.gn_addr.mid, HEX);

    TEST_ASSERT_EQUAL_u64(0xAABBCCDD, lpv.tst, HEX);

    // TODO: Test signed: lpv.latitude
    // TODO: Test signed: lpv.longitude
    TEST_ASSERT_EQUAL_u64(0b1, lpv.pai, BINARY);
    // TODO: Test signed: lpv.speed
    TEST_ASSERT_EQUAL_u64(0x6767, lpv.heading, HEX);

    extract_bits(&test_offset, 0);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.offset_bits, HEX);
    TEST_ASSERT_EQUAL_u64(0x0, test_offset.length, HEX);

    TEST_ASSERT_EQUAL_u64(0x0, test_offset.error.value, HEX);
}


//--------------------------------------------------
void test_geonetworking(){
    test_parse_life_time();
    test_parse_basic_header();

    test_parse_common_flags();
    test_parse_common_header();

    test_parse_gn_addr();
    test_parse_long_position_vector();
}


