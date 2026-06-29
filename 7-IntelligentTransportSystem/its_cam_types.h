// Intelligent Transport System (ITS) - Messages
// > Reference: Cooperative Awareness Message (CAM) - [ETSI EN 302 637-2 V1.4.1 (2019-04)](https://www.etsi.org/deliver/etsi_en/302600_302699/30263702/01.04.01_60/en_30263702v010401p.pdf)

#pragma once
#include "../Util/bit_util.h"
#include "its_common_types.h"


#define GENERATION_DELTA_TIME_BITS BYTE_SIZE * 2
typedef struct {
    unsigned int value: GENERATION_DELTA_TIME_BITS;
} GenerationDeltaTime;


//--------------------------------------------------
// Basic Container
typedef struct {
    StationType station_type;
    ReferencePosition reference_position;
} BasicContainer;


//--------------------------------------------------
// High Frequency Container (HFContainer)
typedef struct {
    Heading heading;
    Speed speed;
    DriveDirection drive_direction;
    VehicleLength vehicle_length;
    VehicleWidth vehicle_width;
    LongitudinalAcceleration longitudinal_acceleration;
    Curvature curvature;
    CurvatureCalculationMode curvature_calculation_mode;
    YawRate yaw_rate;
} BasicVehicleContainerHF;


// TODO:
typedef struct {
} RSUContainerHF;


typedef struct {
    BasicVehicleContainerHF basic_container_hf;
    RSUContainerHF rsu_container_hf;
} HFContainer;


//--------------------------------------------------
typedef struct {
    BasicContainer basic_container;
    HFContainer hf_container;
} CamParameters;


//--------------------------------------------------
void parse_cam_parameters(CamParameters *cam_parameters, DataOffset *data_offset);
void parse_generation_delta_time(GenerationDeltaTime *generation_delta_time, DataOffset *data_offset);

//--------------------------------------------------
void parse_basic_container(BasicContainer *basic_container, DataOffset *data_offset);
void parse_hf_container(HFContainer *hf_container, DataOffset *data_offset);

void parse_basic_vehicle_container_hf(BasicVehicleContainerHF *basic_container_hf, DataOffset *data_offset);
void parse_rsu_container_hf(RSUContainerHF *rsu_container_hf, DataOffset *data_offset);

