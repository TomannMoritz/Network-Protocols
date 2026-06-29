#include "its_cam_types.h"


//--------------------------------------------------
void parse_cam_parameters(CamParameters *cam_parameters, DataOffset *data_offset){
    parse_basic_container(&cam_parameters->basic_container, data_offset);
    parse_hf_container(&cam_parameters->hf_container, data_offset);
}


//--------------------------------------------------
void parse_basic_container(BasicContainer *basic_container, DataOffset *data_offset){
    parse_station_type(&basic_container->station_type, data_offset);
    parse_reference_position(&basic_container->reference_position, data_offset);
}


void parse_hf_container(HFContainer *hf_container, DataOffset *data_offset){
    // TODO: CHOICE

    parse_basic_vehicle_container_hf(&hf_container->basic_container_hf, data_offset);
    // parse_rsu_container_high_frequency(&high_frequency_container->rsuContainerHighFrequency, data_offset);
}


void parse_basic_vehicle_container_hf(BasicVehicleContainerHF *basic_container_hf, DataOffset *data_offset){
    parse_heading(&basic_container_hf->heading, data_offset);
    parse_speed(&basic_container_hf->speed, data_offset);
    parse_drive_direction(&basic_container_hf->drive_direction, data_offset);
    parse_vehicle_length(&basic_container_hf->vehicle_length, data_offset);
    parse_vehicle_width(&basic_container_hf->vehicle_width, data_offset);
    parse_longitudinal_acceleration(&basic_container_hf->longitudinal_acceleration, data_offset);
    parse_curvature(&basic_container_hf->curvature, data_offset);
    parse_curvature_calculation_mode(&basic_container_hf->curvature_calculation_mode, data_offset);
    parse_yaw_rate(&basic_container_hf->yaw_rate, data_offset);
}


void parse_rsu_container_high_frequency(RSUContainerHF *rsu_container_hf, DataOffset *data_offset){
    // TODO:
}


void parse_generation_delta_time(GenerationDeltaTime *generation_delta_time, DataOffset *data_offset){
    generation_delta_time->value = extract_bits(data_offset, GENERATION_DELTA_TIME_BITS).value;
}

