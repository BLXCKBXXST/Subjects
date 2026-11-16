#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define REQUEST_FIFO "request.fifo"
#define RESPONSE_FIFO "response.fifo"
#define RESULT_FILE "output.txt"
#define ERROR_REPLY "ERROR"
#define REQUEST_START "«"
#define REQUEST_END "»"
#define NAME_SIZE 512
#define MESSAGE_SIZE 1024
#define TEXT_SIZE 5000

#endif
