
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
#include <common.h>

#include "helpers.h"

#define MAX_MESSAGE_LENGTH 256
#define MAX_ARGS 16
#define MAX_STR_LENGTH 32
#define DO_CONCURRENT true


typedef struct {
    int sockfd;
    int port;
    pthread_t server_thread;
} server_info_t;

//bool keep_server_running = true;

/**
 * Setup a server and return the the connectioned server_info_t struct
 * @return
 */
server_info_t* setup();

/**
 * Shutdown a server after we are done with it
 * @param info
 */
void teardown(server_info_t* info);

/**
 * Function to handle the client requests
 * @param client_socket_fd
 * @return
 */
void* client_handler(void* client_socket_fd);

/**
 * Execute the client request
 * @param args
 * @return
 */
char* exec_request(char** args);


#endif //SERVER_H
