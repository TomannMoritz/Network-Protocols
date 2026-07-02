// 1-IEEE-1609Dot2
#include "ieee_1609_dot_2.h"


// Note: some header information is before/after the data payload

//--------------------------------------------------
// Pre-Data
void parse_ieee_1609_content_info(Ieee1609Dot2Content *content, DataOffset *data_offset){
    data_offset->offset_bits += IEEE_1609_CONTENT_OFFSET_BITS;
    content->info = extract_bits(data_offset, IEEE_1609_CONTENT_INFO_BITS).value;
}


void parse_ieee_1609_data(Ieee1609Dot2Data *data, DataOffset *data_offset){
    data_offset->offset_bits += IEEE_1609_PROTOCOL_OFFSET_BITS;
    data->protocol_version = extract_bits(data_offset, IEEE_1609_PROTOCOL_VERSION_BITS).value;
    parse_ieee_1609_content_info(&data->content, data_offset);
}


void parse_ieee_1609_dot_2_payload(DataOffset *data_offset){
    u8 extra_byte = extract_bits(data_offset, BYTE_SIZE).value;

    if (extra_byte == IEEE_1609_CONTENT_EXTRA_BYTE){
        data_offset->offset_bits += BYTE_SIZE;
    }
}


//--------------------------------------------------
// Post-Data
void parse_ieee_1609_dot_2_header_info(HeaderInfo *header_info, DataOffset *data_offset){
    parse_ieee_1609_psid(&header_info->psid, data_offset);
    parse_ieee_1609_time_64(&header_info->generation_time, data_offset);
}


void parse_ieee_1609_dot_2_tbs_data(ToBeSignedData *tbs_data, DataOffset *data_offset){
    parse_ieee_1609_dot_2_header_info(&tbs_data->header_info, data_offset);
}


void parse_ieee_1609_dot_2_signed_identifier(SignerIdentifier *identifier, DataOffset *data_offset){
    // TODO
}


//--------------------------------------------------
void parse_ieee_1609_dot_2_pre_signed_unsecure(Ieee1609Dot2Data *signed_data, Ieee1609Dot2SignedContent *signed_content, Ieee1609Dot2Data *unsecure_data, DataOffset *data_offset){
    parse_ieee_1609_data(signed_data, data_offset);
    parse_ieee_1609_hash_algorithm(&signed_content->signed_data.hash_id, data_offset);

    data_offset->offset_bits += BYTE_SIZE;
    parse_ieee_1609_data(unsecure_data, data_offset);
    parse_ieee_1609_dot_2_payload(data_offset);
}


void parse_ieee_1609_dot_2_post_signed(Ieee1609Dot2SignedContent *signed_content, DataOffset *data_offset){
    parse_ieee_1609_dot_2_tbs_data(&signed_content->signed_data.tbs_data, data_offset);
    parse_ieee_1609_dot_2_signed_identifier(&signed_content->signed_data.signer, data_offset);
    parse_ieee_1609_signature(&signed_content->signed_data.signature, data_offset);
}

