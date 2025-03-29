//
// Created by Sam Ogden on 11/1/23.
//

#include "server.h"
#include <stdint.h>
#include "queue.h"
#include <pthread.h>

#define NUM_EXECUTION_THREADS 4

static int listenfd;

Queue queue;

void* client_handler(void* arg) {
    int client_socket_fd = (uintptr_t)arg;

    // Read from client
    char* input_buffer = malloc(MAX_MESSAGE_LENGTH+1);
    memset(input_buffer, 0, MAX_MESSAGE_LENGTH+1);

    // Once we've accepted an incoming request, we can read from it into input_buffer.
    ssize_t bytes_received = recv(client_socket_fd, input_buffer, MAX_MESSAGE_LENGTH, 0);
    if (bytes_received == -1) {
      perror("recv");
      return NULL;
    }

    // Actually do work
    char** args = parse_request(input_buffer);
    process_request(args);

    // We can now send it back.
    ssize_t num_bytes_sent = send(client_socket_fd, "ack", strlen("ack")+1, 0);
    if (num_bytes_sent == -1) {
      perror("send error");
    }
    close(client_socket_fd);
    return NULL;
}

void* run_server(void *pVoid) {
  start_server(PORT);

  pthread_t execution_threads[NUM_EXECUTION_THREADS];
  for (int i = 0; i < NUM_EXECUTION_THREADS; i++) {
    pthread_create(&execution_threads[i], NULL, execution_loop,
      (void *)(uintptr_t)i);
  }

  while (true) {
    int client_socket_fd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    //client_handler((void *)(uintptr_t)client_socket_fd);
    pthread_t client_thread;
    pthread_create(
      &client_thread,
      NULL,
      client_handler,
      (void *)(uintptr_t)client_socket_fd
      );

  }
}

void process_request(char** args) {
  push(&queue, args[0]);
}

void* execution_loop(void* arg) {
  int executor_id = (uintptr_t)arg;
  while (true) {
    char* item = pop(&queue);
    if (item != NULL) {
      log_info("Processed (%d): \"%s\"\n", executor_id, item);
    }
  }
}

void* start_server(void *port) {
  struct addrinfo hints, *res, *p;


  // getaddrinfo for host
  memset (&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo( NULL, (char*)port, &hints, &res) != 0) {
    perror ("getaddrinfo() error");
    exit(1);
  }

  // socket and bind
  for (p = res; p!=NULL; p=p->ai_next) {
    int option = 1;
    listenfd = socket (p->ai_family, p->ai_socktype, 0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (listenfd == -1) continue;
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
  }
  if (p==NULL) {
    perror ("socket() or bind()");
    exit(1);
  }

  freeaddrinfo(res);

  // listen for incoming connections
  if ( listen (listenfd, 1000000) != 0 )
  {
    perror("listen() error");
    exit(1);
  }
  log_info("Listening...\n");
  return NULL;
}

char** parse_request(char* request) {
  char** args = malloc(MAX_ARGS * sizeof(char*));

  if (strlen(request) == 0) {
    args[0] = "";
    args[1] = NULL;
    return args;
  }
  int curr_arg_index = 0;
  char* arg = strtok(request, " ");
  while (arg != NULL) {
    args[curr_arg_index] = malloc(strlen(arg)+1);
    strcpy(args[curr_arg_index], arg);
    arg = strtok(NULL, " ");
    curr_arg_index++;
  }
  args[curr_arg_index] = NULL;

  return args;
}


int main() {
  run_server(NULL);
}