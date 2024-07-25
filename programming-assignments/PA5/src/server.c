
#include "server.h"
#include "database.h"

#include <stdint.h>

#include "student_code.h"

PlayerDatabase db;
pthread_t* server_thread;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <pthread.h>

#define MAX_ATTEMPTS 1000  // Maximum number of attempts to find an open port
#define BACKLOG 10  // Maximum number of pending connections in the queue

int create_server_socket(int *port) {
    int sockfd;
    struct sockaddr_in server_addr;
    int attempts = 0;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Seed the random number generator
    srand(time(NULL));

    // Try binding to a random port
    while (attempts < MAX_ATTEMPTS) {
        *port = rand() % 64512 + 1024;  // Random port between 1024 and 65535
        server_addr.sin_port = htons(*port);

        if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
            // Successfully bound to a port
            if (listen(sockfd, BACKLOG) < 0) {
                perror("listen");
                close(sockfd);
                return -1;
            }
            return sockfd;  // Return the socket file descriptor
        }

        attempts++;
    }

    // Failed to bind to any port after MAX_ATTEMPTS
    close(sockfd);
    return -1;
}

void *start_server_thread(void *arg) {
    server_info_t *server_info = (server_info_t *)arg;
    int sockfd = server_info->sockfd;

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sockfd;

    // printf("Server bound to port: %d\n", server_info->port);
    // printf("Server listening for connections...\n");

    while (1) {
        // Accept a connection
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sockfd < 0) {
            perror("accept");
            close(sockfd);
            free(server_info);
            return NULL;
        }

        // int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        pass_to_client_handler((void *)(uintptr_t)client_sockfd);
    }

    // Close the server socket
    close(sockfd);
    free(server_info);
    return NULL;
}



char** parse_request(char* request) {
  char** args = calloc(MAX_ARGS, sizeof(char*));

  if (strlen(request) == 0) {
    args[0] = "";
    args[1] = NULL;
    return args;
  }

  int i = 0;
  char * token = strtok(request, " ");
  while( token != NULL ) {
    // printf( " %s\n", token ); //printing each token
    args[i] = token;
    // log_debug("\t> %d : %s\n", i, args[i]);
    i++;

    token = strtok(NULL, " ");
  }
  args[i] = NULL;

  return args;
}

void* client_handler(void* arg) {
  int client_socket_fd = (uintptr_t)arg;

  // Prepare buffers
  char* input_buffer = malloc(MAX_MESSAGE_LENGTH+1);
  memset(input_buffer, 0, MAX_MESSAGE_LENGTH+1);

  // Once we've accepted an incoming request, we can read from it into input_buffer.
  ssize_t bytes_received = recv(client_socket_fd, input_buffer, MAX_MESSAGE_LENGTH, 0);
  if (bytes_received == -1) {
    perror("recv");
    return NULL;
  }

  char** args = parse_request(input_buffer);

  char* response = exec_request(args);

  char* output_buffer = malloc(MAX_MESSAGE_LENGTH+1);
  memset(output_buffer, 0, MAX_MESSAGE_LENGTH+1);
  memcpy(output_buffer, response, MAX_MESSAGE_LENGTH);

  // We can now send it back.
  ssize_t num_bytes_sent = send(client_socket_fd, output_buffer, strlen(output_buffer)+1, 0);
  if (num_bytes_sent == -1) {
    perror("send error");
  }
  close(client_socket_fd);

  free(input_buffer);
  free(output_buffer);
  free(response);
  return NULL;
}

char* exec_request(char** args) {
  char* response = calloc(MAX_MESSAGE_LENGTH, 1);
  char* func_name = args[0];

  if (func_name == NULL) {
    sprintf( response, "-1");
  } else if (strcmp("add_player", func_name) == 0) {
    sprintf(
      response,
      "%d",
      add_player(&db, args[1])
      );
  } else if (strcmp("add_player_score", func_name) == 0) {

    if (args[2] == NULL) {
      sprintf( response, "-1");
    } else {
      long int score = strtol(args[2], NULL, 10); // = atoi(args[2]);

      snprintf(
        response,
        MAX_STR_LENGTH - 1,
        "%d",
        add_player_score(&db, args[1], score)
        );
    }

  } else if (strcmp("get_player_plays", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%d",
      get_player_plays(&db, args[1])
      );
  } else if (strcmp("get_player_high_score", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%d",
      get_player_high_score(&db, args[1])
      );


  } else if (strcmp("get_best_player", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%s",
      get_best_player(&db)
      );
  } else if (strcmp("get_num_players", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%d",
      get_num_players(&db)
      );
  } else if (strcmp("get_highest_score", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%d",
      get_highest_score(&db)
      );
  } else if (strcmp("get_total_plays", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%d",
      get_total_plays(&db)
      );


  } else if (strcmp("do_slow_thing", func_name) == 0) {
    snprintf(
      response,
      MAX_STR_LENGTH-1,
      "%d",
      do_slow_thing((float)atoi(args[1]))
      );


  } else {
    sprintf( response, "-1");
  }
  return response;
}


server_info_t* setup() {
  db = init_db();
  server_info_t* server_info = malloc(sizeof(server_info_t));

  if (server_info == NULL) {
      perror("malloc");
      return NULL;
  }

  server_info->sockfd = create_server_socket(&server_info->port);

  if (server_info->sockfd == -1) {
      printf("Failed to bind to any port\n");
      free(server_info);
      return NULL;
  }

  // Create a new thread to run the server
  if (pthread_create(&server_info->server_thread, NULL, start_server_thread, server_info) != 0) {
      perror("pthread_create");
      close(server_info->sockfd);
      free(server_info);
      return NULL;
  }

  pthread_detach(server_info->server_thread);
  fsleep(TIME_DELAY);
  return server_info;
}

void teardown(server_info_t* info) {
  pthread_cancel(info->server_thread);
  free(info);
}

