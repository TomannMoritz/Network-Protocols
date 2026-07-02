# 1-IEEE 1609Dot2

> Reference [ITS ASN1 IEEE 1609Dot2](https://forge.etsi.org/rep/ITS/asn1/ieee1609.2/-/blob/v2017a/README.md?ref_type=tags)


## ToC


## Ieee1609Dot2Data
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `protocol_version`    | unsigned int          | 3-bit     |
| `content`             | Ieee1609Dot2Content   | -         |


### Ieee1609Dot2Content
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `data`                | SignedData            | -         |
| `data`                | UnsecureData          | -         |

> Optional: Choice


#### SignedData
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `hash_id`             | HashAlgorithm         | -         |
| `tbs_data`            | ToBeSignedData        | -         |
| `signer`              | SignerIdentifier      | -         |
| `signature`           | Signature             | -         |


##### UnsecuredData
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `value`               | Opaque                | -         |


##### ToBeSignedData
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `payload`             | SignedDataPayload     | -         |
| `header_info`         | HeaderInfo            | -         |


##### SignedDataPayload
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `data`                | Ieee1609Dot2Data      | -         | OPTIONAL
| `..`                  | ..                    | ..        | ..


##### SignerIdentifier
| Name                  | Type                  | Length    | Info |
|:----------------------|:----------------------|:----------|:-----|
| `digest`              | HashedID8             | -         |
| `certificate`         | SequenceOfCertificate | -         |
| `self`                | NULL                  | -         |

> Optional: Choice


---


## Ieee1609Dot2 Base Types
| Name                  | Type                  | Length    | Info  |
|:----------------------|:----------------------|:----------|:------|
| `PSID`                | unsigned int          | 32-bit    |       |
| `Time64`              | unsigned int          | 64-bit    |       |
| `HashAlgorithm`       | unsigned int          | 8-bit     |       |


### Signature
| Name                  | Type                  | Length    | Info  |
|:----------------------|:----------------------|:----------|:------|
| `signature`           | EcdsaP256Signature    | -         |       |

> Optional other signature types (TODO)


#### EcdsaP256Signature
| Name                  | Type                  | Length    | Info  |
|:----------------------|:----------------------|:----------|:------|
| `r_sig`               | EccP256CurvePoint     | -         |       |
| `s_sig`               | unsigned int          | 32-bit    |       |


##### EccP256CurvePoint
| Name                  | Type                  | Length    | Info  |
|:----------------------|:----------------------|:----------|:------|
| `x_only`              | unsigned int          | 32-bit    |       |
| `compressed_y_0`      | unsigned int          | 32-bit    |       |
| `compressed_y_1`      | unsigned int          | 32-bit    |       |
| `compressed_x`        | unsigned int          | 32-bit    |       |
| `compressed_y`        | unsigned int          | 32-bit    |       |



