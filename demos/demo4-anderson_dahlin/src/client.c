//
// Created by Sam Ogden on 11/14/23.
//

#include "client.h"

#define NUM_REQUESTS 10

void* make_request(void* msg) {
  struct sockaddr_in dest_addr;

  int sockfd = socket(AF_INET,SOCK_STREAM,0);

  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(strtol("5005", NULL, 10));
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

int main(void) {
  pthread_t* threads[NUM_REQUESTS];
  for (int i = 0; i < NUM_REQUESTS; i++) {
    char* string_to_send = malloc(10);
    sprintf(string_to_send, "%d", i);
    threads[i] = make_request_async(string_to_send);
  }
  for (int i = 0; i < NUM_REQUESTS; i++) {
    void* resp;
    pthread_join(*threads[i], &resp);
    printf("resp: \"%s\"\n", (char*)resp);
  }

}