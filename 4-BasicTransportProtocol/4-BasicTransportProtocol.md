# 4-BasicTransportProtocol

> Reference [ETSI EN 302 636-5-1 V2.1.0 (2017-05)](https://www.etsi.org/deliver/etsi_en/302600_302699/3026360501/02.01.00_20/en_3026360501v020100a.pdf)

## Overview
- BTP-A: *interactive* packet trasnport
- BTP-B: *non-interactive* packet transport


BTP Header type is set in the *Next Header* (*NH*) field of the GeoNetworking *Common Header*.

| Next Header   | Encoding  | Description   |
|:--------------|:----------|:--------------|
| BTP-A         | 1         | BTP-A Header  |
| BTP-B         | 2         | BTP-B Header  |


## BTP Headers
### BTP-A
| Name              | Type          | Length    | Info  |
|:------------------|:--------------|:----------|:------|
| destination_port  | unsigned int  | 16-bit    |
| source_port       | unsigned int  | 16-bit    |


### BTP-B
| Name                  | Type          | Length    | Info  |
|:----------------------|:--------------|:----------|:------|
| destination_port      | unsigned int  | 16-bit    |
| destination_port_info | unsigned int  | 16-bit    |


## BTP Port Numbers
| Port  | Facilities Service/Application    | Related Standard  |
|:------|:----------------------------------|:------------------|
| 2_001 | CA (CAM)                          | ETSI EN 302 637-2 |
| 2_002 | DEN (DENM)                        | ETSI EN 302 637-3 |
| 2_003 | RLT (MAPEM)                       | ETSI TS 103 301   |
| 2_004 | TLM (SPATEM)                      | ETSI TS 102 301   |
| ..    | ..                                | ..                |
| 2_006 | IVI (IVIM)                        | ETSI TS 103 301   |
| ..    | ..                                | ..                |


> Reference [ETSI TS 103 248 V2.1.1 (2021-08)](https://www.etsi.org/deliver/etsi_ts/103200_103299/103248/02.01.01_60/ts_103248v020101p.pdf)

