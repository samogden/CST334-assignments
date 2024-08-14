#include "../include/client.h"


void* make_request(void* msg) {

  int port = ((client_msg*)msg)->port;
  char* msg_str = ((client_msg*)msg)->msg;

  // log_debug("port: %d\n", port);
  // log_debug("msg_str: %s\n", msg_str);

  size_t num_bits_written;
  char* response_buffer = calloc(sizeof(response_buffer), 1024);

  // do-while loop to resend messages that are cut-off early, since SIGPIPE seems to be thrown silently.
  do {

    struct sockaddr_in dest_addr;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    dest_addr.sin_zero[8]='\0';

    connect(sockfd,(struct sockaddr*)&dest_addr, sizeof(struct sockaddr));
    num_bits_written = write(sockfd, msg_str, strlen(msg_str));
    if (num_bits_written == -1) {
      // Then something failed and we'll need to resend
      fsleep(TIME_DELAY / 100.0);
    } else {
      recv(sockfd, response_buffer, sizeof(response_buffer), 0);
    }
    close(sockfd);
  } while (num_bits_written < sizeof(msg_str) || (strcmp(response_buffer, "-1") == 0));


  return response_buffer;
}

pthread_t* make_request_async(void* msg) {
  pthread_t* t = malloc(sizeof(pthread_t));
  pthread_create(t, NULL, make_request, msg);
  return t;
}
