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

