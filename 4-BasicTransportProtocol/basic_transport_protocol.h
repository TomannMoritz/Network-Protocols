// 4-BasicTransportProtocl
#pragma once

#include "../Util/bit_util.h"


//--------------------------------------------------
#define BTP_A_HEADER (1)
#define BTP_B_HEADER (2)

#define BTP_CAM_PORT    (2001)
#define BTP_DENM_PORT   (2002)
#define BTP_MAPEM_PORT  (2003)
#define BTP_SPATEM_PORT (2004)

#define BTP_IVIM_PORT   (2006)


//--------------------------------------------------
#define BTP_A_DESTINATION_PORT_BITS (16)
#define BTP_A_SOURCE_PORT_BITS (16)
typedef struct {
    u32 destination_port: BTP_A_DESTINATION_PORT_BITS;
    u32 source_port: BTP_A_SOURCE_PORT_BITS;
} BTP_A;


#define BTP_B_DESTINATION_PORT_BITS (16)
#define BTP_B_DESTINATION_PORT_INFO_BITS (16)
typedef struct {
    u32 destination_port: BTP_B_DESTINATION_PORT_BITS;
    u32 destination_port_info: BTP_B_DESTINATION_PORT_INFO_BITS;
} BTP_B;


//--------------------------------------------------
void parse_btp_a(BTP_A *btp_a, DataOffset *data_offset);
void parse_btp_b(BTP_B *btp_b, DataOffset *data_offset);


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_basic_transport_protocol();
