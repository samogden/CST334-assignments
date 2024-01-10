
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

#include "common.h"

#define MAX_MESSAGE_LENGTH 256
#define MAX_ARGS 16
#define MAX_STR_LENGTH 32
#define DO_CONCURRENT true

#define PORT "5005"
//bool keep_server_running = true;


extern pthread_t server_thread;

void setup();
void teardown();

void* startServer(void* port);
void* run_server(void *pVoid);
void* client_handler(void* client_socket_fd);
char* exec_request(char** args);

void* make_request(void* msg);
pthread_t* make_request_async(void* msg);


#endif //SERVER_H
