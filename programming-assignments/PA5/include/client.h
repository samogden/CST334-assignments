#ifndef CLIENT_H
#define CLIENT_H


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
#include <pthread.h>

#include <common.h>

#include "helpers.h"

#define MAX_MSG_LENGTH 100

typedef struct {
  int port;
  char msg[MAX_MSG_LENGTH+1];
} client_msg;

void* make_request(void* msg); // struct client_msg
pthread_t* make_request_async(void* msg);

#endif //CLIENT_H
