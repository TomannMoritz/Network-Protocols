#include "its_messages.h"

void parse_coop_awareness(CoopAwareness *coop_awareness, DataOffset *data_offset){
    parse_generation_delta_time(&coop_awareness->generation_delta_time, data_offset);

    data_offset->offset_bits += 4;
    parse_cam_parameters(&coop_awareness->cam_parameters, data_offset);
}


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_its_messages(){
    TEST_ASSERT_EQUAL_u64(1, 2, NUM);
    // TODO:
}

