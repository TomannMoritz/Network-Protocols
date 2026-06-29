#include "ethernet.h"

int main(void){
    int socket_fd = setup();

    FILE *log_fd = stdout;
    start(socket_fd, log_fd);

    return 0;
}
