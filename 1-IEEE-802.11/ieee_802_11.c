// IEEE 802.11

#include "ieee_802_11.h"


void parse_ieee_802_11_frame_control(FrameControl *frame_control, DataOffset *data_offset){
    frame_control->sub_type = extract_bits(data_offset, FRAME_CONTROL_SUB_TYPE_BITS).value;
    frame_control->type = extract_bits(data_offset, FRAME_CONTROL_TYPE_BITS).value;
    frame_control->version = extract_bits(data_offset, FRAME_CONTROL_VERSION_BITS).value;
}


void parse_ieee_802_11_flags(Flags *flags, DataOffset *data_offset){
    flags->htc_order = extract_bits(data_offset, FLAGS_HTC_ORDER_BITS).value;
    flags->f_protected = extract_bits(data_offset, FLAGS_PROTECTED_BITS).value;
    flags->more_data = extract_bits(data_offset, FLAGS_MORE_DATA_BITS).value;
    flags->pwr_mgt = extract_bits(data_offset, FLAGS_PWR_MGT_BITS).value;
    flags->retry = extract_bits(data_offset, FLAGS_RETRY_BITS).value;
    flags->more_fragments = extract_bits(data_offset, FLAGS_MORE_FRAGMENTS_BITS).value;
    flags->ds_status = extract_bits(data_offset, FLAGS_DS_STATUS).value;
}


void parse_ieee_802_11_qos_control(QoSControl *qos_control, DataOffset *data_offset){
    qos_control->payload_type = extract_bits(data_offset, QOS_PAYLOAD_TYPE_BITS).value;
    qos_control->ack_policy = extract_bits(data_offset, QOS_ACK_POLICY_BITS).value;
    qos_control->qos = extract_bits(data_offset, QOS_QOS_BITS).value;
    qos_control->t_id = extract_bits(data_offset, QOS_T_ID_BITS).value;
    qos_control->txop = extract_bits(data_offset, QOS_TXOP_BITS).value;

    // TODO: qos_control->priority
}


void parse_ieee_802_11(IEEE_802_11 *ieee, DataOffset *data_offset){
    parse_ieee_802_11_frame_control(&ieee->frame_control, data_offset);
    parse_ieee_802_11_flags(&ieee->flags, data_offset);

    extract_bits(data_offset, IEEE_802_11_RESERVED_BITS);
    ieee->duration = extract_bits(data_offset, IEEE_802_11_DURATION_BITS).value;
    ieee->receiver = extract_bits(data_offset, IEEE_802_11_RECEIVER_BITS).value;
    ieee->sender = extract_bits(data_offset, IEEE_802_11_SENDER_BITS).value;
    ieee->bss_id = extract_bits(data_offset, IEEE_802_11_BSS_ID_BITS).value;
    ieee->sn_l = extract_bits(data_offset, IEEE_802_11_SN_L_BITS).value;
    ieee->fragment_number = extract_bits(data_offset, IEEE_802_11_FRAGMENT_NUMBER_BITS).value;
    ieee->sn_h = extract_bits(data_offset, IEEE_802_11_SN_H_BITS).value;

    parse_ieee_802_11_qos_control(&ieee->qos_control, data_offset);
}

