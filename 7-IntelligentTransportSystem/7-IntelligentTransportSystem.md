# 7-Intelligent Transport System (ITS)

> Reference: Cooperative Awareness Message (CAM) - [ETSI EN 302 637-2 V1.4.1 (2019-04)](https://www.etsi.org/deliver/etsi_en/302600_302699/30263702/01.04.01_60/en_30263702v010401p.pdf)
> <br>
> Reference: Common Data Dictionary - [ETSI TS 102 894-2 V1.3.1 (2018-08)](https://www.etsi.org/deliver/etsi_ts/102800_102899/10289402/01.03.01_60/ts_10289402v010301p.pdf)

## ToC
- Messages
    - CAM
        - ItsPduHeader
        - CoopAwareness
            - GenerationDeltaTime
            - CamParameters
                - Basic Container
                - HF Container
                - LF Container
                - Extra Container (Optional)
- Types
- Common Types


## ITS
### Header/Messages
#### CAM

| Name              | Type          | Info |
|:------------------|:--------------|:-----|
| `its_pdu`         | ItsPduHeader  |
| `coop_awareness`  | CoopAwareness |

##### CoopAwareness

| Name                      | Type                  | Info |
|:--------------------------|:----------------------|:-----|
| `generation_delta_time`   | GenerationDeltaTime   |
| `cam_parameters`          | CamParameters         |

###### CamParameters

| Name                  | Type              | Info |
|:----------------------|:------------------|:-----|
| `basic_container`     | BasicContainer    |
| `hf_container`        | HFContainer       |
| `special_container`   | SpecialContainer  |
| `..`                  | SpecialContainer  |


---


### Types
#### BasicContainer

| Name                          | Type                      | Info |
|:------------------------------|:--------------------------|:-----|
| `station_type`                | StationType               |
| `reference_position`          | ReferencePosition         |


#### HFContainer

| Name                          | Type                      | Info |
|:------------------------------|:--------------------------|:-----|
| `basic_vehicle_container_hf`  | BasicVehicleContainerHF   |
| `rsu_container_hf`            | RSUContainerHF            |

##### BasicVehicleContainerHF

| Name                          | Type                      | Info |
|:------------------------------|:--------------------------|:-----|
| `heading`                     | Heading                   |
| `speed`                       | Speed                     |
| `drive_direction`             | DriveDirection            |
| `vehicle_length`              | VehicleLength             |
| `vehicle_width`               | VehicleWidth              |
| `longitudinal_acceleration`   | LongitudinalAcceleration  |
| `curvature`                   | Curvature                 |
| `curvature_calculation_mode`  | CurvatureCalculationMode  |
| `yaw_rate`                    | YawRate                   |

##### RSUContainerHF

| Name                          | Type                      | Info |
|:------------------------------|:--------------------------|:-----|
| `TODO`                        | TODO                      |


#### LFContainer
> TODO


---


### Common Types
#### Data Element (DE)

| ID    | Type                              | Type          | Length    | Range                             | Info |
|:------|:----------------------------------|:--------------|:----------|:----------------------------------|:-----|
| A.1   | `AccelerationConfidence`          | unsigned int  | 7-bit     | (0..102)                          |
| A.8   | `AltitudeConfidence`              | unsigned int  | 4-bit     | (0..15)                           |
| A.9   | `AltitudeValue`                   | unsigned int  | 20-bit    | (-100_000..800_001)               |
| A.13  | `CurvatureCalculationMode`        | unsigned int  | 2-bit     | (0..2)                            |
| A.14  | `CurvatureConfidence`             | unsigned int  | 3-bit     | (0..7)                            |
| A.15  | `CurvatureValue`                  | signed int    | 15-bit    | (-30_000..30_001)                 |
| A.22  | `DriveDirection`                  | unsigned int  | 2-bit     | (0..2)                            |
| A.34  | `HeadingConfidence`               | unsigned int  | 7-bit     | (1..127)                          |
| A.35  | `HeadingValue`                    | unsigned int  | 12-bit    | (0..3_601)                        |
| A.41  | `Latitude`                        | signed int    | 31-bit    | (-900_000_000..900_000_001)       |
| A.44  | `Longitude`                       | signed int    | 31-bit    | (-1_800_000_000..1_800_000_001)   |
| A.45  | `LongitudinalAccelerationValue`   | signed int    | 9-bit     | (-160..161)                       |
| A.67  | `SemiAxisLength`                  | unsigned int  | 12-bit    | (0..4_095)                        |
| A.72  | `SemiConfidence`                  | unsigned int  | 7-bit     | (1..127)                          |
| A.74  | `SpeedValue`                      | unsigned int  | 14-bit    | (0..16_383)                       |
| A.77  | `StationID`                       | unsigned int  | 32-bit    | (0..4_294_967_295)                |
| A.78  | `StationType`                     | unsigned int  | 8-bit     | (0..255)                          |
| A.91  |`VehicleLengthConfidenceIndication`| unsigned int  | 3-bit     | (0..4)                            |
| A.92  | `VehicleLengthValue`              | unsigned int  | 10-bit    | (1..1023)                         |
| A.94  | `VehicleRole`                     | unsigned int  | 4-bit     | (0..15)                           |
| A.95  | `VehicleWidth`                    | unsigned int  | 6-bit     | (1..62)                           |
| A.96  | `VerticalAccelerationValue`       | signed int    | 9-bit     | (-160..161)                       |
| A.100 | `YawRateConfidence`               | unsigned int  | 4-bit     | (0..8)                            |
| A.101 | `YawRateValue`                    | signed int    | 15-bit     | (-32_766..32_767)                |



#### Data Frame (DF)
##### Altitude
> A.103

| Name                      | Type                  | Info |
|:--------------------------|:----------------------|:-----|
| `altitude_value`          | AltitudeValue         |
| `altitude_confidence`     | AltitudeConfidence    |


##### Curvature
> A.107

| Name                      | Type                  | Info |
|:--------------------------|:----------------------|:-----|
| `curvature_value`         | CurvatureValue        |
| `curvature_confidence`    | CurvatureConfidence   |


##### Heading
> A.112

| Name                      | Type                  | Info |
|:--------------------------|:----------------------|:-----|
| `heading_value`           | HeadingValue          |
| `heading_confidence`      | HeadingConfidence     |


##### ItsPduHeader
> A.114

| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `protocol_version`| unsigned int  | 8-bit     |
| `message_id`      | unsigned int  | 8-bit     |
| `station_id`      | StationID     | -         |


##### LongitudinalAcceleration
> A.116

| Name                                  | Type                                  | Info |
|:--------------------------------------|:--------------------------------------|:-----|
| `longitudinal_acceleration_value`     | LongitudinalAccelerationValue         |
| `longitudinal_acceleration_confidence`| LongitudinalAccelerationConfidence    |


##### PosConfidenceEllipse
> A.119

| Name                          | Type              | Info |
|:------------------------------|:------------------|:-----|
| `semi_major_confidence`       | SemiAxisLength    |
| `semi_minor_confidence`       | SemiAxisLength    |
| `semi_major_orientation`      | HeadingValue      |


##### ReferencePosition
> A.124

| Name                          | Type                  | Info |
|:------------------------------|:----------------------|:-----|
| `latitude`                    | Latitude              |
| `longitude`                   | Longitude             |
| `position_confidence_ellipse` | PosConfidenceEllipse  |
| `altitude`                    | Altitude              |


##### Speed
> A.126

| Name                          | Type              | Info |
|:------------------------------|:------------------|:-----|
| `speed_value`                 | SpeedValue        |
| `speed_confidence`            | SpeedConfidence   |


##### VehicleLength
> A.131

| Name                          | Type                      | Info |
|:------------------------------|:--------------------------|:-----|
| `vehicle_length_value`        | VehicleLengthValue        |
| `vehicle_length_confidence`   | VehicleLengthConfidence   |


##### YawRate
> A.132

| Name                          | Type                      | Info |
|:------------------------------|:--------------------------|:-----|
| `yaw_rate_value`              | YawRateValue              |
| `yaw_rate_confidence`         | YawRateConfidence         |

