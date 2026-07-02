// 1-IEEE-1609Dot2
#pragma once
#include "../Util/bit_util.h"

#include "ieee_1609_dot_2_base_types.h"


//--------------------------------------------------
typedef struct {
    PSID psid;
    Time64 generation_time;
} HeaderInfo;


typedef struct {
    // NOTE: SignedDataPayload
    HeaderInfo header_info;
} ToBeSignedData;


typedef struct {
} SignerIdentifier;


typedef struct {
    HashAlgorithm hash_id;
    ToBeSignedData tbs_data;
    SignerIdentifier signer;
    Signature signature;
} SignedData;


typedef struct {
    SignedData signed_data;
} Ieee1609Dot2SignedContent;


#define Ieee1609UnsecuredContent (0)
#define Ieee1609SignedContent (1)

#define IEEE_1609_CONTENT_EXTRA_BYTE (0x81)

// TODO: check size
#define IEEE_1609_CONTENT_OFFSET_BITS (4)
#define IEEE_1609_CONTENT_INFO_BITS (4)
typedef struct {
    u32 info: IEEE_1609_CONTENT_INFO_BITS;
} Ieee1609Dot2Content;


#define IEEE_1609_PROTOCOL_OFFSET_BITS (5)
#define IEEE_1609_PROTOCOL_VERSION_BITS (3)
typedef struct {
    u32 protocol_version: IEEE_1609_PROTOCOL_VERSION_BITS;
    Ieee1609Dot2Content content;
} Ieee1609Dot2Data;



//--------------------------------------------------
void parse_ieee_1609_dot_2_pre_signed_unsecure(Ieee1609Dot2Data *signed_data, Ieee1609Dot2SignedContent *signed_content, Ieee1609Dot2Data *unsecure_data, DataOffset *data_offset);
void parse_ieee_1609_dot_2_post_signed(Ieee1609Dot2SignedContent *signed_content, DataOffset *data_offset);


