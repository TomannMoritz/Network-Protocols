#include "its_common_types.h"


//--------------------------------------------------
// Data Element (DE)

void parse_acceleration_confidence(AccelerationConfidence *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, ACCELERATION_CONFIDENCE_BITS).value;
}

void parse_altitude_confidence(AltitudeConfidence *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, ALTITUDE_CONFIDENCE_BITS).value;
}

void parse_altitude_value(AltitudeValue *value, DataOffset *data_offset){
    value->value = extract_bits(data_offset, ALTITUDE_VALUE_BITS).value + ALTITUDE_VALUE_OFFSET;
}

void parse_curvature_calculation_mode(CurvatureCalculationMode *mode, DataOffset *data_offset){
    mode->value = extract_bits(data_offset, CURVATURE_CALCULATION_MODE_BITS).value;
}

void parse_curvature_confidence(CurvatureConfidence *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, CURVATURE_CONFIDENCE_BITS).value;
}

void parse_curvature_value(CurvatureValue *value, DataOffset *data_offset){
    value->value = (signed long int)extract_bits(data_offset, CURVATURE_VALUE_BITS).value + CURVATURE_VALUE_OFFSET;
}

void parse_drive_direction(DriveDirection *drive_direction, DataOffset *data_offset){
    drive_direction->value = extract_bits(data_offset, DRIVE_DIRECTION_BITS).value;
}

void parse_heading_confidence(HeadingConfidence *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, HEADING_CONFIDENCE_BITS).value;
}

void parse_heading_value(HeadingValue *value, DataOffset *data_offset){
    value->value = extract_bits(data_offset, HEADING_VALUE_BITS).value;
}

void parse_latitude(Latitude *latitude, DataOffset *data_offset){
    signed long int extracted_value = (signed long int)extract_bits(data_offset, LATITUDE_BITS).value;
    latitude->value = extracted_value + LATITUDE_OFFSET;
}

void parse_longitude(Longitude *longitude, DataOffset *data_offset){
    signed long int extracted_value = (signed long int)extract_bits(data_offset, LONGITUDE_BITS).value;

    longitude->value = extracted_value + LONGITUDE_OFFSET;
}

void parse_longitudinal_acceleration_value(LongitudinalAccelerationValue *value, DataOffset *data_offset){
    signed long int extracted_value = (signed long int)extract_bits(data_offset, LONGITUDINAL_ACCELERATION_VALUE_BITS).value;
    value->value = extracted_value + LONGITUDINAL_ACCELERATION_VALUE_OFFSET;
}

void parse_semi_axis_length(SemiAxisLength *length, DataOffset *data_offset){
    length->value = extract_bits(data_offset, SEMI_AXIS_LENGTH_BITS).value;
}

void parse_speed_confidence(SpeedConfidence *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, SPEED_CONFIDENCE_BITS).value;
}

void parse_speed_value(SpeedValue *value, DataOffset *data_offset){
    value->value = extract_bits(data_offset, SPEED_VALUE_BITS).value;
}

void parse_station_id(StationID *id, DataOffset *data_offset){
    id->value = extract_bits(data_offset, ITS_STATION_ID_BITS).value;
}

void parse_station_type(StationType *type, DataOffset *data_offset){
    type->value = extract_bits(data_offset, STATION_TYPE_BITS).value;
}

void parse_vehicle_length_confidence_indication(VehicleLengthConfidenceIndication *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, VEHICLE_LENGTH_CONFIDENCE_INDICATION_BITS).value;
}

void parse_vehicle_length_value(VehicleLengthValue *value, DataOffset *data_offset){
    value->value = extract_bits(data_offset, VEHICLE_LENGTH_VALUE_BITS).value;
}

void parse_vehicle_role(VehicleRole *role, DataOffset *data_offset){
    role->value = extract_bits(data_offset, VEHICLE_ROLE_BITS).value;
}

void parse_vehicle_width(VehicleWidth *width, DataOffset *data_offset){
    width->value = extract_bits(data_offset, VEHICLE_WIDTH_BITS).value;
}

void parse_vertical_acceleration_value(VerticalAccelerationValue *value, DataOffset *data_offset){
    value->value = extract_bits(data_offset, VERTICAL_ACCELERATION_VALUE_BITS).value;
    
}

void parse_yaw_rate_confidence(YawRateConfidence *confidence, DataOffset *data_offset){
    confidence->value = extract_bits(data_offset, YAW_RATE_CONFIDENCE_BITS).value;
}

void parse_yaw_rate_value(YawRateValue *value, DataOffset *data_offset){
    signed long int extracted_value = (signed long int)extract_bits(data_offset, YAW_RATE_VALUE_BITS).value;
    value->value = extracted_value + YAW_RATE_VALUE_OFFSET;
}


//--------------------------------------------------
// Data Frame (Data Frame)
void parse_altitude(Altitude *altitude, DataOffset *data_offset){
    parse_altitude_value(&altitude->altitiude_value, data_offset);
    parse_altitude_confidence(&altitude->altitude_confidence, data_offset);
}

void parse_curvature(Curvature *curvature, DataOffset *data_offset){
    parse_curvature_value(&curvature->curvature_value, data_offset);

    data_offset->offset_bits += 1;
    parse_curvature_confidence(&curvature->curvature_confidence, data_offset);
}

void parse_heading(Heading *heading, DataOffset *data_offset){
    parse_heading_value(&heading->heading_value, data_offset);
    parse_heading_confidence(&heading->heading_confidence, data_offset);
}

void parse_its_pdu_header(ItsPduHeader *its_pdu_header, DataOffset *data_offset){
    its_pdu_header->protcol_version = extract_bits(data_offset, ITS_PROTOCOL_VERSION_BITS).value;
    its_pdu_header->message_id = extract_bits(data_offset, ITS_MESSAGE_ID_BITS).value;

    parse_station_id(&its_pdu_header->station_id, data_offset);
}

void parse_longitudinal_acceleration(LongitudinalAcceleration *longitudinal_acceleration, DataOffset *data_offset){
    parse_longitudinal_acceleration_value(&longitudinal_acceleration->longitudinal_acceleration_value, data_offset);
    parse_acceleration_confidence(&longitudinal_acceleration->acceleration_confidence, data_offset);
}

void parse_pos_confidence_ellipse(PosConfidenceEllipse *pos_confidence_ellipse, DataOffset *data_offset){
    parse_semi_axis_length(&pos_confidence_ellipse->semi_major_confidence, data_offset);
    parse_semi_axis_length(&pos_confidence_ellipse->semi_minor_confidence, data_offset);
    parse_heading_value(&pos_confidence_ellipse->heading_value, data_offset);
}

void parse_reference_position(ReferencePosition *reference_position, DataOffset *data_offset){
    parse_latitude(&reference_position->latitude, data_offset);

    data_offset->offset_bits += REFERENCE_POSITION_RESERVED_BITS;
    parse_longitude(&reference_position->longitude, data_offset);
    parse_pos_confidence_ellipse(&reference_position->position_confidence_ellipse, data_offset);
    parse_altitude(&reference_position->altitiude, data_offset);
}

void parse_speed(Speed *speed, DataOffset *data_offset){
    parse_speed_value(&speed->speed_value, data_offset);
    parse_speed_confidence(&speed->speed_confidence, data_offset);
}

void parse_vehicle_length(VehicleLength *vehicle_length, DataOffset *data_offset){
    parse_vehicle_length_value(&vehicle_length->vehicle_length_value, data_offset);
    parse_vehicle_length_confidence_indication(&vehicle_length->vehicle_length_confidenceIndication, data_offset);
}

void parse_yaw_rate(YawRate *yaw_rate, DataOffset *data_offset){
    parse_yaw_rate_value(&yaw_rate->yaw_rate_value, data_offset);
    parse_yaw_rate_confidence(&yaw_rate->yaw_rate_confidence, data_offset);
}

