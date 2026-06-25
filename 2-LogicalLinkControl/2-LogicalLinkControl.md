# Logical Link Control

## ToC
- [Logical Link Control](#logicallinkcontrol)
    - [DSAP](#dsap)
    - [SSAP](#ssap)
    - [Control Field](#controlfield)


## LogicalLinkControl
| Name                  | Type          | Length    | Info |
|:----------------------|:--------------|:----------|:-----|
| `dsap`                | DSAP          | -         |
| `ssap`                | SAP           | -         |
| `control_field`       | ControlField  | -         |
| `organization_code`   | unsigned int  | 24-bit    |
| `type`                | unsigned int  | 16-bit    |


### DSAP
| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `sap`             | unsigned int  | 7-bit     |
| `ig`              | unsigned int  | 1-bit     |


### SSAP
| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `sap`             | unsigned int  | 7-bit     |
| `cr`              | unsigned int  | 1-bit     |


### ControlField
| Name              | Type          | Length    | Info |
|:------------------|:--------------|:----------|:-----|
| `command`         | unsigned int  | 6-bit     |
| `frame_type`      | unsigned int  | 2-bit     |


