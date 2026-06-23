// Types
#pragma once

//--------------------------------------------------
// Basic Types
#define False (0)
#define True (1)

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long int u64;

typedef signed char s8;
typedef signed int s32;
typedef signed long int s64;


//--------------------------------------------------
#define OPTIONAL_ERROR_BITS (1)
typedef struct {
    int value: OPTIONAL_ERROR_BITS;
} Error;

#define OPTIONAL_ERROR_RETURN(optional)  \
    if (optional.error.value){ \
        return optional; \
    }


typedef struct {
    u8 value;
    Error error;
} Optional_u8;


typedef struct {
    u32 value;
    Error error;
} Optional_u32;


typedef struct {
    u64 value;
    Error error;
} Optional_u64;

typedef struct {
    s8 value;
    Error error;
} Optional_s8;


typedef struct {
    s32 value;
    Error error;
} Optional_s32;


typedef struct {
    s64 value;
    Error error;
} Optional_s64;

