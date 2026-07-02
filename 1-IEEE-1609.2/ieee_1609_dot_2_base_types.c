// 1-IEEE-1609Dot2-BaseTypes

#include "ieee_1609_dot_2_base_types.h"


//--------------------------------------------------
void parse_ieee_1609_psid(PSID *psid, DataOffset *data_offset){
    psid->value = extract_bits(data_offset, IEEE_1609_PSID_BITS).value;
}


void parse_ieee_1609_time_64(Time64 *time_64, DataOffset *data_offset){
    time_64->value = extract_bits(data_offset, IEEE_1609_TIME_64_BITS).value;
}


void parse_ieee_1609_hash_algorithm(HashAlgorithm *hash_algorithm, DataOffset *data_offset){
    hash_algorithm->value = extract_bits(data_offset, HASH_ALGORITHM_BITS).value;
}


//--------------------------------------------------
void parse_ieee_1609_eccp_256_curve_point(EccP256CurvePoint *curve_point, DataOffset *data_offset){
    curve_point->x_only = extract_bits(data_offset, CURVE_POINT_X_ONLY_BITS).value;
    curve_point->compressed_y_0 = extract_bits(data_offset, CURVE_POINTS_COMPRESSED_Y_0_BITS).value;
    curve_point->compressed_y_1 = extract_bits(data_offset, CURVE_POINTS_COMPRESSED_Y_1_BITS).value;
    curve_point->uncompressed_x = extract_bits(data_offset, CURVE_POINTS_UNCOMPRESSED_X_BITS).value;
    curve_point->uncompressed_y = extract_bits(data_offset, CURVE_POINTS_UNCOMPRESSED_Y_BITS).value;
}


void parse_ieee_1609_ecdsap_256_signature(EcdsaP256Signature *signature, DataOffset *data_offset){
    parse_ieee_1609_eccp_256_curve_point(&signature->r_sig, data_offset);
    signature->s_sig = extract_bits(data_offset, ECDSAP256_SSIG_BITS).value;
}


void parse_ieee_1609_signature(Signature *signature, DataOffset *data_offset){
    parse_ieee_1609_ecdsap_256_signature(&signature->signature, data_offset);
}
