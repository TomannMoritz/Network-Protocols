#include "its_messages.h"
#include "its_cam_types.c"


void parse_cam(ItsPduHeader *header, CoopAwareness *cam, DataOffset *data_offset){
    parse_its_pdu_header(header, data_offset);
    parse_coop_awareness(cam, data_offset);
}


void parse_coop_awareness(CoopAwareness *coop_awareness, DataOffset *data_offset){
    parse_generation_delta_time(&coop_awareness->generation_delta_time, data_offset);
    parse_cam_parameters(&coop_awareness->cam_parameters, data_offset);
}


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_its_messages(){
    // TODO:
}

