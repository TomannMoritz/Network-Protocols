// 1-IEEE-1609Dot2-BaseTypes
#pragma once
#include "../Util/bit_util.h"


//--------------------------------------------------
#define IEEE_1609_PSID_BITS (32)
typedef struct {
    u32 value: IEEE_1609_PSID_BITS;
} PSID;


#define IEEE_1609_TIME_64_BITS (64)
typedef struct {
    u64 value: IEEE_1609_TIME_64_BITS;
} Time64;


#define HASH_ALGORITHM_BITS (8)
typedef struct {
    u32 value: HASH_ALGORITHM_BITS;
} HashAlgorithm;


//--------------------------------------------------
#define CURVE_POINT_X_ONLY_BITS (32)
#define CURVE_POINTS_COMPRESSED_Y_0_BITS (32)
#define CURVE_POINTS_COMPRESSED_Y_1_BITS (32)
#define CURVE_POINTS_UNCOMPRESSED_X_BITS (32)
#define CURVE_POINTS_UNCOMPRESSED_Y_BITS (32)
typedef struct {
    u32 x_only: CURVE_POINTS_UNCOMPRESSED_X_BITS;
    u32 compressed_y_0: CURVE_POINTS_COMPRESSED_Y_0_BITS;
    u32 compressed_y_1: CURVE_POINTS_COMPRESSED_Y_1_BITS;
    u32 uncompressed_x: CURVE_POINTS_UNCOMPRESSED_X_BITS;
    u32 uncompressed_y: CURVE_POINTS_UNCOMPRESSED_Y_BITS;
} EccP256CurvePoint;


#define ECDSAP256_SSIG_BITS (48)
typedef struct {
    EccP256CurvePoint r_sig;
    u64 s_sig: ECDSAP256_SSIG_BITS;
} EcdsaP256Signature;


// OPTIONAL other types
typedef struct {
    EcdsaP256Signature signature;
} Signature;


//--------------------------------------------------
void parse_ieee_1609_psid(PSID *psid, DataOffset *data_offset);
void parse_ieee_1609_time_64(Time64 *time_64, DataOffset *data_offset);
void parse_ieee_1609_hash_algorithm(HashAlgorithm *hash_algorithm, DataOffset *data_offset);


//--------------------------------------------------
void parse_ieee_1609_signature(Signature *signature, DataOffset *data_offset);
