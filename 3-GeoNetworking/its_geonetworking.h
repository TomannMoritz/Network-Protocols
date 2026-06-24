// GeoNetworking
#pragma once
#include "../Util/bit_util.h"
#include "../Util/logger.h"


//--------------------------------------------------
// Life Time
#define LIFETIME_MULTIPLIER_BITS (6)
#define LIFETIME_BASE_BITS (2)
typedef struct {
    u32 multiplier: LIFETIME_MULTIPLIER_BITS;
    u32 base: LIFETIME_BASE_BITS;
} LifeTime;


// Basic Header
#define BASIC_VERSION_BITS (4)
#define BASIC_NEXT_HEADER_BITS (4)
#define BASIC_RESERVED_BITS (8)
#define BASIC_RHL_BITS (8)
typedef struct {
    u32 version: BASIC_VERSION_BITS;
    u32 next_header: BASIC_NEXT_HEADER_BITS;
    LifeTime life_time;
    u32 rhl: BASIC_RHL_BITS;
} BasicHeader;


//--------------------------------------------------
// Common Flags
#define COMMON_FLAG_MOBILE_BITS (1)
#define COMMON_FLAG_RESERVED_BITS (7)
typedef struct {
    u32 mobile: COMMON_FLAG_MOBILE_BITS;
} CommonFlags;


// Common Header
#define COMMON_NEXT_HEADER_BITS (4)
#define COMMON_RESERVED_BITS_1 (4)
#define COMMON_HEADER_TYPE_BITS (4)
#define COMMON_HEADER_SUB_TYPE_BITS (4)
#define COMMON_TRAFFIC_CLASS_BITS (8)
#define COMMON_PAYLOAD_LENGTH_BITS (16)
#define COMMON_MHL_BITS (8)
#define COMMON_RESERVED_BITS_2 (8)
typedef struct {
    u32 next_header: COMMON_NEXT_HEADER_BITS;
    u32 header_type: COMMON_HEADER_TYPE_BITS;
    u32 header_sub_type: COMMON_HEADER_SUB_TYPE_BITS;
    u32 traffic_class: COMMON_TRAFFIC_CLASS_BITS;
    CommonFlags common_flags;
    u32 payload_length: COMMON_PAYLOAD_LENGTH_BITS;
    u32 mhl: COMMON_MHL_BITS;
} CommonHeader;


//--------------------------------------------------
// GN ADDR
#define GN_ADDR_MANUAL_BITS (1)
#define GN_ADDR_STATION_TYPE_BITS (5)
#define GN_ADDR_RESERVED_BITS (10)
#define GN_ADDR_MID_BITS (48)
typedef struct {
    u32 manual: GN_ADDR_MANUAL_BITS;
    u32 station_type: GN_ADDR_STATION_TYPE_BITS;
    u64 mid: GN_ADDR_MID_BITS;
} GN_ADDR;


#define LPV_GN_ADDR_BITS (64)
#define LPV_TST_BITS (32)
#define LPV_LATITUDE_BITS (32)
#define LPV_LONGITUDE_BITS (32)
#define LPV_PAI_BITS (1)
#define LPV_SPEED_BITS (15)
#define LPV_HEADING_BITS (16)
typedef struct {
    GN_ADDR gn_addr;
    u32 tst: LPV_TST_BITS;
    s32 latitude: LPV_LATITUDE_BITS;
    s32 longitude: LPV_LONGITUDE_BITS;
    u32 pai: LPV_PAI_BITS;
    s32 speed: LPV_SPEED_BITS;
    u32 heading: LPV_HEADING_BITS;
} LongPositionVector;


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_geonetworking();

