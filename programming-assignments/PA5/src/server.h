//
// Created by Sam Ogden on 11/1/23.
//

#ifndef PA5_SERVER_H
#define PA5_SERVER_H

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


#define log_debug(...) fprintf(stderr, "DEBUG:"); fprintf(stderr, __VA_ARGS__);
#define log_info(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__);
#define log_error(...) fprintf(stderr, "ERROR:"); fprintf(stderr, __VA_ARGS__);

extern pthread_t server_thread;

void setup();
void teardown();

void* startServer(void* port);
void* run_server(void *pVoid);
void* client_handler(void* client_socket_fd);
char* exec_request(char** args);

void* make_request(void* msg);
pthread_t* make_request_async(void* msg);

#define SERVERPORT "5005"  // The port the server will be listening on.
#define SERVERHOST "localhost"  // Assume localhost for now


#endif //PA5_SERVER_H
