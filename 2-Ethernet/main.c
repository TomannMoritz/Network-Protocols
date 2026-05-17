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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>


#define BYTE_SIZE 8
#define ADDR_BYTES 6
#define TYPE_BYTES 2

#define MIN_FRAME_SIZE (DATA_OFFSET + MIN_PAYLOAD_SIZE + CRC_BYTES)
#define HEADER_BYTES (ADDR_BYTES + ADDR_BYTES + TYPE_BYTES)
#define MIN_PAYLOAD_BYTES 42
#define CRC_BYTES 4
#define MAX_MTU_BYTES (1 << 16)

#define UNPRINTABLE_CHAR '.'
#define SPACE_CHAR ' '

#define HEX_FORMAT "%02X "
#define HEX_FORMAT_OFFSET 3

#define LOG_VALUE(fd, x) fprintf(fd, "\t%s = %lx\n", #x, x)


// TODO: parse CRC
typedef struct {
    unsigned long int addr_destination: ADDR_BYTES * BYTE_SIZE;
    unsigned long int addr_source: ADDR_BYTES * BYTE_SIZE;
    unsigned short ether_type: TYPE_BYTES * BYTE_SIZE;
    int crc: CRC_BYTES;
    unsigned char data[MAX_MTU_BYTES];
    int payload_size;
} ethernet_frame;


// logging
void log_frame_header(FILE *log_fd, ethernet_frame *frame){
    fprintf(log_fd, "\n[Ethernet] - Size: %d\n", frame->payload_size + HEADER_BYTES);
    LOG_VALUE(log_fd, frame->addr_destination);
    LOG_VALUE(log_fd, frame->addr_source);
    LOG_VALUE(log_fd, frame->ether_type);
}


void log_frame_data(FILE *log_fd, ethernet_frame *frame, int line_size){
    unsigned char *p = frame->data;
    char hex_buff[line_size * 4] = {};
    char char_buff[line_size * 2] = {};

    const char *DATA_FORMAT = "\n\t\t%s%s\t%s";

    int offset;
    for (int i = 0; i < frame->payload_size; i++, p++){
        offset = i % line_size;

        if (offset == 0){
            fprintf(log_fd, DATA_FORMAT, hex_buff, "", char_buff);
        }

        sprintf(hex_buff + offset * HEX_FORMAT_OFFSET, HEX_FORMAT, *p);
        sprintf(char_buff + offset, "%c", isprint(*p) ? *p: UNPRINTABLE_CHAR);
    }

    // add last line spacing
    char space[line_size * HEX_FORMAT_OFFSET] = {};
    int space_to_fill = (line_size - offset) * HEX_FORMAT_OFFSET;
    for (int i = 0; i < space_to_fill; i++){
        space[i] = SPACE_CHAR;
    }
    fprintf(log_fd, DATA_FORMAT, hex_buff, space, char_buff);
    fprintf(log_fd, "\n");
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

    frame->addr_destination = *(unsigned long int*)buff;
    frame->addr_source = *(unsigned long int*)(buff + ADDR_BYTES);
    frame->ether_type = *(unsigned short*)(buff + ADDR_BYTES + ADDR_BYTES);
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


int main(void){
    int socket_fd = setup();

    FILE *log_fd = stdout;
    start(socket_fd, log_fd);

    return 0;
}
