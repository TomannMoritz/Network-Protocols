# 7-Vehicle2Everything

## Technology Overview/Protocols
| Layer             | Protocol                              | Info      |
|:------------------|:--------------------------------------|:----------|
| 1: Physical       | IEEE 802.11                           |
| 2: Data Link      | Logical Link Control (LLC)            |
| 3: Routing        | GeoNetwork                            | IEEE 1609.2
| 4: Transport      | Basic Transport Protocol (BTP)        |
| 7: Application    | Intelligent Transport Protocol (ITS)  |


## Compilation
```bash
gcc -g ../Util/*.c ../1-IEEE-1609.2/*.c  ../1-IEEE-802.11/*.c ../2-LogicalLinkControl/*.c ../3-GeoNetworking/*.c ../4-BasicTransportProtocol/*.c ../7-IntelligentTransportSystem/*.c -o testing testing.c
```


