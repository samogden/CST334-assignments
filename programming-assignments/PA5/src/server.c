
#include "server.h"
#include "database.h"

#include <stdint.h>

#include "student_code.h"


static int listenfd;
PlayerDatabase db;

pthread_t* server_thread;


//start server from https://gist.github.com/laobubu/d6d0e9beb934b60b2e552c2d03e1409e
void* startServer(void *port) {
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

void * run_server(void *pVoid) {

  db = init_db();

  startServer(PORT);

  // ACCEPT connections
  // Help from https://stackoverflow.com/a/45642760
  while (true) {
    int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    pass_to_client_handler((void *)(uintptr_t)connfd);
  }
}

char** parse_request(char* request) {
  log_debug("'%s'\n", request);
  char** args = calloc(MAX_ARGS, sizeof(char*));

  if (strlen(request) == 0) {
    args[0] = "";
    args[1] = NULL;
    return args;
  }

  int i = 0;
  char * token = strtok(request, " ");
  while( token != NULL ) {
    printf( " %s\n", token ); //printing each token
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
  //int client_socket_fd = *((int*)client_socket_fd_ptr);

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
  ssize_t num_bytes_sent = send(client_socket_fd, output_buffer, bytes_received+1, 0);
  if (num_bytes_sent == -1) {
    perror("send error");
  }
  close(client_socket_fd);

  free (input_buffer);
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




void* make_request(void* msg) {
  struct sockaddr_in dest_addr;

  int sockfd = socket(AF_INET,SOCK_STREAM,0);

  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(strtol(PORT, NULL, 10));
  dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  dest_addr.sin_zero[8]='\0';

  connect(sockfd,(struct sockaddr*)&dest_addr, sizeof(struct sockaddr));

  write(sockfd, (char*)msg, strlen(msg));

  char* buffer = calloc(sizeof(buffer), 1024);
  recv(sockfd, buffer, sizeof(buffer), 0);

  close(sockfd);

  return buffer;
}

pthread_t* make_request_async(void* msg) {
  pthread_t* t = malloc(sizeof(pthread_t));
  pthread_create(t, NULL, make_request, msg);
  return t;
}

void setup() {
  server_thread = malloc(sizeof(pthread_t));
  pthread_create(server_thread, NULL, run_server, "5005");
  pthread_detach(*server_thread);
  fsleep(TIME_DELAY);
}

void teardown() {
  pthread_cancel(*server_thread);
  free(server_thread);
}

