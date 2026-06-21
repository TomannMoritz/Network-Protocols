#pragma once
#include "../Util/logger.h"
#include "../Util/bit_util.h"

int setup();
void start(int socket_fd, FILE *log_fd);
