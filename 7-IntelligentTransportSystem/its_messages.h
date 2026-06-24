// Intelligent Transport System (ITS) - Messages
// > Reference: Cooperative Awareness Message (CAM) - [ETSI EN 302 637-2 V1.4.1 (2019-04)](https://www.etsi.org/deliver/etsi_en/302600_302699/30263702/01.04.01_60/en_30263702v010401p.pdf)

#pragma once
#include "its_cam_types.h"

typedef struct {
    GenerationDeltaTime generation_delta_time;
    CamParameters cam_parameters;
} CoopAwareness;


typedef struct {
    ItsPduHeader header;
    CoopAwareness coop_awareness; 
} CAM;


//--------------------------------------------------
// Functions

void parse_its_pdu_header(ItsPduHeader *header, DataOffset *data_offset);
void parse_coop_awareness(CoopAwareness *coop_awareness, DataOffset *data_offset);


//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_its_messages();
