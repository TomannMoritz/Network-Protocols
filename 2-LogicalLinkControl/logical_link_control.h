// Logical Link Control
#pragma once
#include "../Util/bit_util.h"


#define DSAP_SAP_BITS (7)
#define DSAP_IG_BITS (1)
typedef struct {
    u32 sap: DSAP_SAP_BITS;
    u32 ig: DSAP_IG_BITS;
} DSAP;


#define SSAP_SAP_BITS (7)
#define SSAP_CR_BITS (1)
typedef struct {
    u32 sap: SSAP_SAP_BITS;
    u32 cr: SSAP_CR_BITS;
} SSAP;


#define CONTROL_FIELD_COMMAND_BITS (6)
#define CONTROL_FIELD_FRAME_TYPE (2)
typedef struct {
    u32 command: CONTROL_FIELD_COMMAND_BITS;
    u32 frame_type: CONTROL_FIELD_FRAME_TYPE;
} ControlField;


#define LLC_ORGANIZATION_CODE_BITS (24)
#define LLC_TYPE_BITS (16)
typedef struct {
    DSAP dsap;
    SSAP ssap;
    ControlField control_field;
    u32 organization_code: LLC_ORGANIZATION_CODE_BITS;
    u32 type: LLC_TYPE_BITS;
} LogicalLinkControl;


//--------------------------------------------------
void parse_logical_link_control(LogicalLinkControl *llc, DataOffset *data_offset);

