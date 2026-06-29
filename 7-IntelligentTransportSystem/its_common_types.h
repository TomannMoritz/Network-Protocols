// Common ITS Data Dictionary
// Reference: Common Data Dictionary - [ETSI TS 102 894-2 V1.3.1 (2018-08)](https://www.etsi.org/deliver/etsi_ts/102800_102899/10289402/01.03.01_60/ts_10289402v010301p.pdf)

#pragma once
#include "../Util/bit_util.h"

//--------------------------------------------------
// Data Element (DE)

#define ACCELERATION_CONFIDENCE_BITS (7)
typedef struct {
    unsigned int value: ACCELERATION_CONFIDENCE_BITS;
} AccelerationConfidence;


#define ALTITUDE_CONFIDENCE_BITS (4)
typedef struct {
    unsigned char value: ALTITUDE_CONFIDENCE_BITS;
} AltitudeConfidence;


#define ALTITUDE_VALUE_OFFSET (-100000)
#define ALTITUDE_VALUE_BITS (20)
typedef struct {
    signed int value: ALTITUDE_VALUE_BITS;
} AltitudeValue;


#define CURVATURE_CALCULATION_MODE_BITS (2)
typedef struct {
    unsigned int value: CURVATURE_CALCULATION_MODE_BITS;
} CurvatureCalculationMode;


#define CURVATURE_CONFIDENCE_BITS (3)
typedef struct {
    unsigned int value: CURVATURE_CONFIDENCE_BITS;
} CurvatureConfidence;


#define CURVATURE_VALUE_OFFSET (-30000)
#define CURVATURE_VALUE_BITS (15)
typedef struct {
    signed int value: CURVATURE_VALUE_BITS;
} CurvatureValue;


#define DRIVE_DIRECTION_BITS (2)
typedef struct {
    unsigned int value: DRIVE_DIRECTION_BITS; 
} DriveDirection;


#define HEADING_CONFIDENCE_BITS (7)
typedef struct {
    unsigned int value: HEADING_CONFIDENCE_BITS;
} HeadingConfidence;


#define HEADING_VALUE_BITS (12)
typedef struct {
    unsigned int value: HEADING_VALUE_BITS;
} HeadingValue;


#define LATITUDE_OFFSET (-900000000)
#define LATITUDE_BITS ((8 * 4) - 1)
typedef struct {
    signed int value: LATITUDE_BITS;
} Latitude;


#define LONGITUDE_OFFSET (-1800000000)
#define LONGITUDE_BITS ((BYTE_SIZE * 4) - 1)
typedef struct {
    signed int value: LONGITUDE_BITS;
} Longitude;


#define LONGITUDINAL_ACCELERATION_VALUE_OFFSET (-160)
#define LONGITUDINAL_ACCELERATION_VALUE_BITS (9)
typedef struct {
    signed int value: LONGITUDINAL_ACCELERATION_VALUE_BITS;
} LongitudinalAccelerationValue;


#define SEMI_AXIS_LENGTH_BITS (12)
typedef struct {
    unsigned int value: SEMI_AXIS_LENGTH_BITS;
} SemiAxisLength;


#define SPEED_CONFIDENCE_BITS (7)
typedef struct {
    unsigned int value;
} SpeedConfidence;


#define SPEED_VALUE_BITS (14)
typedef struct {
    unsigned int value: SPEED_VALUE_BITS;
} SpeedValue;


#define ITS_STATION_ID_BITS (BYTE_SIZE * 4)
typedef struct {
    unsigned int value: ITS_STATION_ID_BITS;
} StationID;


#define STATION_TYPE_BITS (BYTE_SIZE)
typedef struct {
    unsigned char value: STATION_TYPE_BITS;
} StationType;


#define VEHICLE_LENGTH_CONFIDENCE_INDICATION_BITS (3)
typedef struct {
    unsigned int value: VEHICLE_LENGTH_CONFIDENCE_INDICATION_BITS;
} VehicleLengthConfidenceIndication;


#define VEHICLE_LENGTH_VALUE_BITS (10)
typedef struct {
    unsigned int value: VEHICLE_LENGTH_VALUE_BITS;
} VehicleLengthValue;


#define VEHICLE_ROLE_BITS (4)
typedef struct {
    unsigned int value: VEHICLE_ROLE_BITS;
} VehicleRole;


#define VEHICLE_WIDTH_BITS (6)
typedef struct {
    unsigned int value;
} VehicleWidth;


#define VERTICAL_ACCELERATION_VALUE_BITS 9
typedef struct {
    unsigned int value: VERTICAL_ACCELERATION_VALUE_BITS;
} VerticalAccelerationValue;


#define YAW_RATE_CONFIDENCE_BITS (4)
typedef struct {
    unsigned int value: YAW_RATE_CONFIDENCE_BITS;
} YawRateConfidence;


#define YAW_RATE_VALUE_OFFSET (-32768)
#define YAW_RATE_VALUE_BITS (15)
typedef struct {
    signed int value: YAW_RATE_VALUE_BITS;
} YawRateValue;


//--------------------------------------------------
// Data Frame (Data Frame)
typedef struct {
    AltitudeValue altitiude_value;
    AltitudeConfidence altitude_confidence;
} Altitude;


#define CURVATURE_RESERVED_BITS (1)
typedef struct {
    CurvatureValue curvature_value;
    CurvatureConfidence curvature_confidence;
} Curvature;


typedef struct {
    HeadingValue heading_value;
    HeadingConfidence heading_confidence;
} Heading;


#define ITS_PROTOCOL_VERSION_BITS (BYTE_SIZE)
#define ITS_MESSAGE_ID_BITS (BYTE_SIZE)
typedef struct {
    unsigned char protcol_version: ITS_PROTOCOL_VERSION_BITS;
    unsigned char message_id: ITS_MESSAGE_ID_BITS;
    StationID station_id;
} ItsPduHeader;


typedef struct {
    LongitudinalAccelerationValue longitudinal_acceleration_value;
    AccelerationConfidence acceleration_confidence;
} LongitudinalAcceleration;


typedef struct {
    SemiAxisLength semi_major_confidence;
    SemiAxisLength semi_minor_confidence;
    HeadingValue heading_value;
} PosConfidenceEllipse;


#define REFERENCE_POSITION_RESERVED_BITS (1)
typedef struct {
    Latitude latitude;
    Longitude longitude;
    PosConfidenceEllipse position_confidence_ellipse;
    Altitude altitiude;
} ReferencePosition;


typedef struct {
    SpeedValue speed_value;
    SpeedConfidence speed_confidence;
} Speed;


typedef struct {
    VehicleLengthValue vehicle_length_value;
    VehicleLengthConfidenceIndication vehicle_length_confidenceIndication;
} VehicleLength;


typedef struct {
    YawRateValue yaw_rate_value;
    YawRateConfidence yaw_rate_confidence;
} YawRate;


//--------------------------------------------------
void parse_heading(Heading *heading, DataOffset *data_offset);
void parse_speed(Speed *speed, DataOffset *data_offset);
void parse_drive_direction(DriveDirection *drive_direction, DataOffset *data_offset);


void parse_vehicle_length(VehicleLength *vehicle_length, DataOffset *data_offset);
void parse_vehicle_width(VehicleWidth *width, DataOffset *data_offset);
void parse_longitudinal_acceleration(LongitudinalAcceleration *longitudinal_acceleration, DataOffset *data_offset);
void parse_curvature(Curvature *curvature, DataOffset *data_offset);
void parse_curvature_calculation_mode(CurvatureCalculationMode *mode, DataOffset *data_offset);
void parse_yaw_rate(YawRate *yaw_rate, DataOffset *data_offset);

void parse_station_type(StationType *type, DataOffset *data_offset);
void parse_reference_position(ReferencePosition *reference_position, DataOffset *data_offset);

//--------------------------------------------------
// Testing
//--------------------------------------------------
void test_its_common_types();

