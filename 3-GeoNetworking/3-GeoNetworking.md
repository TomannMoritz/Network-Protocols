# 3-GeoNetworking

> Reference: [ETSI EN 302 636-4-1 (V1.3.0: 2017-05)](https://www.etsi.org/deliver/etsi_en/302600_302699/3026360401/01.04.01_30/en_3026360401v010401v.pdf)


## ToC
- [GeoNetworking Types](#types)
    - [Topologically-Scoped Broadcast](#tbs)
    - [Geographically-Scoped Broadcast](#gsc)
- [Basic Header](#basic)
    - Version (4-bit)
    - Next Header (4-bit)
    - *RESERVED* (8-bit)
    - [LifeTime](#lifetime)
        - Multiplier (6-bit)
        - Base (2-bit)
    - RHL (8-bit)
- [Common Header](#common)
    - Next Header (4-bit)
    - *RESERVED* (4-bit)
    - Header Type (4-bit)
    - Header SubType (4-bit)
    - Traffic Class (8-bit)
    - [Common Flags](#commonflags)
        - Mobile (1-bit)
        - *RESERVED* (7-bit)
    - Payload Length (16-bit)
    - MHL (8-bit)
    - *RESERVED* (8-bit)
- [Extended Header](#extended)


## GeoNetworking Header
### Types
#### TSB
> Topologically-Scoped Broadcast: 9.8.3

| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `basic_header`    | BasicHeader   | -         |
| `common_header`   | CommonHeader  | -         |
| `sn`              | unsigned int  | 16-bit    | Sequence Number
| `_`               | -             | 8-bit     | *RESERVED*
| `lpv`             | LPV           | -         |


#### GBC
> Geographically-Scoped Broadcast: 9.8.5

| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `basic_header`    | BasicHeader   | -         |
| `common_header`   | CommonHeader  | -         |
| `sn`              | unsigned int  | 16-bit    | Sequence Number
| `_`               | -             | 8-bit     | *RESERVED*
| `lpv`             | LPV           | -         |
| `latitude`        | unsigned int  | 32-bit    |
| `longitude`       | unsigned int  | 32-bit    |
| `radius`          | unsigned int  | 16-bit    |
| `distance`        | unsigned int  | 16-bit    |
| `angle`           | unsigned int  | 16-bit    |
| `_`               | unsigned int  | 16-bit    | *RESERVED*

---

### Basic
> Basic Header: 9.6

| Name          | Type          | Length    | Info |
|:--------------|:--------------|:----------|:-----|
| `version`     | unsigned int  | 4-bit     |
| `next_header` | unsigned int  | 4-bit     |
| `_`           | -             | 8-bit     | *RESERVED*
| `life_time`   | LifeTime      | -         |
| `rhl`         | unsigned int  | 8-bit     | Remaining Hop Limit


#### LifeTime
> Life Time: 9.6.4

| Name          | Type          | Length    | Info |
|:--------------|:--------------|:----------|:-----|
| `multiplier`  | unsigned int  | 6-bit     |
| `base`        | unsigned int  | 2-bit     |

---

### Common
> Common Header: 9.7

| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `next_header`     | unsigned int  | 4-bit     |
| `_`               | -             | 4-bit     | *RESERVED*
| `header_type`     | unsigned int  | 4-bit     |
| `header_sub_type` | unsigned int  | 4-bit     |
| `traffic_class`   | unsigned int  | 8-bit     |
| `flags`           | CommonFlags   | -         |
| `payload_length`  | unsigned int  | 16-bit    |
| `mhl`             | unsigned int  | 8-bit     | Maximum Hop Limit
| `_`               | -             | 8-bit     | *RESERVED*


#### CommonFlags

| Name          | Type          | Length    | Info |
|:--------------|:--------------|:----------|:-----|
| `mobile`      | unsigned int  | 1-bit     | Station mobile/stationary
| `_`           | -             | 7-bit     | *RESERVED*

---

### LPV
> Long Position Vector: 9.5.2

| Name          | Type          | Length    | Info |
|:--------------|:--------------|:----------|:-----|
| `gn_addr`     | GN_ADDR       | -         |
| `tst`         | unsigned int  | 32-bit    | TimeSTamp
| `latitude`    | unsigned int  | 32-bit    | Latitude
| `longitude`   | unsigned int  | 32-bit    | Longitude
| `pai`         | unsigned int  | 1-bit     | Position Accuracy Indicator
| `speed`       | unsigned int  | 15-bit    | Speed (0,01 m/s)
| `heading`     | unsigned int  | 16-bit    | Degree from North (0,1 deg)


### GN_ADDR
> GeoNetworking Address: 6.3


| Name          | Type          | Length    | Info |
|:--------------|:--------------|:----------|:-----|
| `manual`      | unsigned int  | 1-bit     | Manually configured network address
| `st`          | unsigned int  | 5-bit     | Station Type
| `_`           | -             | 10-bit    | *RESERVED*
| `mid`         | unsigned int  | 48-bit    | MAC ID
