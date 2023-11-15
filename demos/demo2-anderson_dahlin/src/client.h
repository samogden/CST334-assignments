//
// Created by Sam Ogden on 11/14/23.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>

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


void* make_request(void* msg);
pthread_t* make_request_async(void* msg);

#endif //CLIENT_H
