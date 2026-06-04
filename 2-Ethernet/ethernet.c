/*
2-Ethernet
Reference: https://en.wikipedia.org/wiki/Ethernet_frame

Ethernet frame:

0           2            4           6           8            10          12          14            (64-1522)
|-----|-----|-----|------|-----|-----|-----|-----|-----|------|-----|-----|------|-----|-----|--...---|-----|-----|-----|------|
|           MAC destination          |          MAC source                | Ethertype  | Payload/Data |         CRC            |
|------------------------------------|------------------------------------|------------|--------...---|------------------------|


- MAC destination:  receiver/target address (FF:FF:FF:FF:FF:FF - Broadcast)
- MAC source:       sender address
- Ethertype:        Length/Type
- Payload/Data:     (Size: 42-1500 Bytes)
- CRC:              Frame check sequence (CRC: Cyclic redundancy check)
*/


#include "../Util/logger.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>

#define ADDR_BYTES 6
#define TYPE_BYTES 2

#define MIN_FRAME_SIZE (DATA_OFFSET + MIN_PAYLOAD_SIZE + CRC_BYTES)
#define HEADER_BYTES (ADDR_BYTES + ADDR_BYTES + TYPE_BYTES)
#define MIN_PAYLOAD_BYTES 42
#define CRC_BYTES 4
#define MAX_MTU_BYTES (1 << 16)


typedef struct {
    unsigned long int addr_destination: ADDR_BYTES * BYTE_SIZE;
    unsigned long int addr_source: ADDR_BYTES * BYTE_SIZE;
    unsigned short ether_type: TYPE_BYTES * BYTE_SIZE;
    unsigned char data[MAX_MTU_BYTES];
    int payload_size;
} ethernet_frame;


// logging
void log_frame_header(FILE *log_fd, ethernet_frame *frame){
    fprintf(log_fd, "\n[Ethernet] - Size: %d\n", frame->payload_size + HEADER_BYTES);

    char *buf = alloca(ADDR_SPACE_STR * 2);
    format_mac_address(frame->addr_destination, buf);
    format_mac_address(frame->addr_source, buf + ADDR_SPACE_STR);

    LOG_STR_VALUE(log_fd, frame->addr_destination, buf);
    LOG_STR_VALUE(log_fd, frame->addr_source, buf + ADDR_SPACE_STR);
    LOG_VALUE(log_fd, frame->ether_type);
}


void log_frame_data(FILE *log_fd, ethernet_frame *frame, int line_size){
    log_byte_data(log_fd, frame->data, frame->payload_size, line_size);
}


int setup(){
    printf("Setup Ethernet Socket..\n");
    int socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (socket_fd == -1){
        fprintf(stderr, "Could not create ethernet socket!\n");
        exit(1);
    }

    return socket_fd;
}


void save_frame(unsigned char *buff, ethernet_frame *frame, int size){
    // copy only the payload/data
    memcpy(&frame->data, buff + HEADER_BYTES, size - HEADER_BYTES);

    frame->addr_destination = convert_address_bit_numbering(*(unsigned long int*)buff);
    frame->addr_source = convert_address_bit_numbering(*(unsigned long int*)(buff + ADDR_BYTES));
    frame->ether_type = convert_address_bit_numbering(*(unsigned short*)(buff + ADDR_BYTES + ADDR_BYTES)) >> BYTE_SIZE * (ADDR_BYTES - sizeof(short int));
    frame->payload_size = size - HEADER_BYTES;
}


void start(int socket_fd, FILE *log_fd){
    int buf_size = 1 << 16;
    unsigned char input_buffer[buf_size];
    ethernet_frame frame = {};

    int line_size = 32;

    // read received packets
    while (1){
        int bytes_read = recv(socket_fd, &input_buffer, buf_size, 0);
        if (bytes_read <= 0){ continue; }

        // TODO: filter other packets
        // check min ethernet frame size
        if (bytes_read < MIN_PAYLOAD_BYTES){ continue; }

        save_frame(input_buffer, &frame, bytes_read);

        // logging
        if (log_fd == NULL){ continue; }
        log_frame_header(log_fd, &frame);
        log_frame_data(log_fd, &frame, line_size);
    }
}
