// Logical Link Control

#include "logical_link_control.h"


void parse_llc_dsap(DSAP *dsap, DataOffset *data_offset){
    dsap->sap = extract_bits(data_offset, DSAP_SAP_BITS).value;
    dsap->ig = extract_bits(data_offset, DSAP_IG_BITS).value;
}


void parse_llc_ssap(SSAP *ssap, DataOffset *data_offset){
    ssap->sap = extract_bits(data_offset, SSAP_SAP_BITS).value;
    ssap->cr = extract_bits(data_offset, SSAP_CR_BITS).value;
}


void parse_llc_control_field(ControlField *control_field, DataOffset *data_offset){
    control_field->command = extract_bits(data_offset, CONTROL_FIELD_COMMAND_BITS).value;
    control_field->frame_type = extract_bits(data_offset, CONTROL_FIELD_FRAME_TYPE).value;
}


void parse_logical_link_control(LogicalLinkControl *llc, DataOffset *data_offset){
    parse_llc_dsap(&llc->dsap, data_offset);
    parse_llc_ssap(&llc->ssap, data_offset);
    parse_llc_control_field(&llc->control_field, data_offset);

    llc->organization_code = extract_bits(data_offset, LLC_ORGANIZATION_CODE_BITS).value;
    llc->type = extract_bits(data_offset, LLC_TYPE_BITS).value;
}


//--------------------------------------------------
// Testing
//--------------------------------------------------

//--------------------------------------------------
void test_logical_link_control(){
    // TODO:
    TEST_ASSERT_EQUAL_u64(0, 2, NUM);
}
