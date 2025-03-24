//
// Created by Sam Ogden on 11/1/23.
//

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#define MAX_MESSAGE_LENGTH 256
#define MAX_ARGS 16
#define MAX_STR_LENGTH 32
#define DO_CONCURRENT true

#define PORT "5005"
//bool keep_server_running = true;


#define log_debug(...) fprintf(stderr, "DEBUG:"); fprintf(stderr, __VA_ARGS__)
#define log_info(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__)
#define log_error(...) fprintf(stderr, "ERROR:"); fprintf(stderr, __VA_ARGS__)


void* start_server(void* port);
void* run_server(void *pVoid);
void* execution_loop(void* arg);
void process_request(char** args);
char** parse_request(char* request);


#endif //SERVER_H
