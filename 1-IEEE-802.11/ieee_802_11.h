// IEEE 802.11
#pragma once
#include "../Util/bit_util.h"


#define FRAME_CONTROL_SUB_TYPE_BITS (4)
#define FRAME_CONTROL_TYPE_BITS (2)
#define FRAME_CONTROL_VERSION_BITS (2)
typedef struct {
    u32 sub_type: FRAME_CONTROL_SUB_TYPE_BITS;
    u32 type: FRAME_CONTROL_TYPE_BITS;
    u32 version: FRAME_CONTROL_VERSION_BITS;
} FrameControl;


#define FLAGS_HTC_ORDER_BITS (1)
#define FLAGS_PROTECTED_BITS (1)
#define FLAGS_MORE_DATA_BITS (1)
#define FLAGS_PWR_MGT_BITS (1)
#define FLAGS_RETRY_BITS (1)
#define FLAGS_MORE_FRAGMENTS_BITS (1)
#define FLAGS_DS_STATUS (2)
typedef struct {
    u32 htc_order : FLAGS_HTC_ORDER_BITS;
    u32 f_protected: FLAGS_PROTECTED_BITS;
    u32 more_data: FLAGS_MORE_DATA_BITS;
    u32 pwr_mgt: FLAGS_PWR_MGT_BITS;
    u32 retry: FLAGS_RETRY_BITS;
    u32 more_fragments: FLAGS_MORE_FRAGMENTS_BITS;
    u32 ds_status: FLAGS_DS_STATUS;
} Flags;


#define QOS_PAYLOAD_TYPE_BITS (1)
#define QOS_ACK_POLICY_BITS (2)
#define QOS_QOS_BITS (1)
#define QOS_T_ID_BITS (4)
#define QOS_TXOP_BITS (8)
#define QOS_PRIORITY_BITS (3)
typedef struct {
    u32 payload_type: QOS_PAYLOAD_TYPE_BITS;
    u32 ack_policy: QOS_ACK_POLICY_BITS;
    u32 qos: QOS_QOS_BITS;
    u32 t_id: QOS_T_ID_BITS;
    u32 txop: QOS_TXOP_BITS;
    u32 priority: QOS_PRIORITY_BITS;
} QoSControl;


#define IEEE_802_11_RESERVED_BITS (1)
#define IEEE_802_11_DURATION_BITS (15)
#define IEEE_802_11_RECEIVER_BITS (48)
#define IEEE_802_11_SENDER_BITS (48)
#define IEEE_802_11_BSS_ID_BITS (48)
#define IEEE_802_11_SN_L_BITS (4)
#define IEEE_802_11_FRAGMENT_NUMBER_BITS (4)
#define IEEE_802_11_SN_H_BITS (8)
typedef struct {
    FrameControl frame_control;
    Flags flags;
    u64 duration: IEEE_802_11_DURATION_BITS;
    u64 receiver: IEEE_802_11_RECEIVER_BITS;
    u64 sender: IEEE_802_11_SENDER_BITS;
    u64 bss_id: IEEE_802_11_BSS_ID_BITS;
    u64 sn_l: IEEE_802_11_SN_L_BITS;
    u64 fragment_number: IEEE_802_11_FRAGMENT_NUMBER_BITS;
    u64 sn_h: IEEE_802_11_SN_H_BITS;
    QoSControl qos_control;
} IEEE_802_11;


void parse_ieee_802_11(IEEE_802_11 *ieee, DataOffset *data_offset);


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_ieee_802_dot_11();
