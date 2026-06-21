#include "2-Ethernet/ethernet.h"
#include "2-Ethernet/ethernet.c"


int main(void){
    int socket_fd = setup();

    FILE *log_fd = stdout;
    start(socket_fd, log_fd);

    return 0;
}
