
/* 
 * This is like sync_buf.c except that the synchronized buffer is
 * structured as a thread-safe object.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_WRITES 100

typedef struct SBUF {
  // sync vars
  pthread_mutex_t lock;
  pthread_cond_t read_go;
  pthread_cond_t write_go;

  // state vars
  int buf;
  int count;
} SBUF;

SBUF *sbuf_create() {
  SBUF *sbuf = (SBUF *)malloc(sizeof(SBUF));

  // initialize synchronization variables
  pthread_mutex_init(&sbuf->lock, NULL);
  pthread_cond_init(&sbuf->read_go, NULL);
  pthread_cond_init(&sbuf->write_go, NULL);

  // initialize state variables
  sbuf->count = 0;

  return sbuf;
}

int sbuf_read(SBUF *sbuf) {
  pthread_mutex_lock(&sbuf->lock);

  while (sbuf->count != 1) {
	pthread_cond_wait(&sbuf->read_go, &sbuf->lock);
  }

  // do the read
  int var = sbuf->buf;
  sbuf->count = 0;

  // let the writer know
  pthread_cond_signal(&sbuf->write_go);

  pthread_mutex_unlock(&sbuf->lock);
  return var;
}

void sbuf_write(SBUF *sbuf, int val) {
  pthread_mutex_lock(&sbuf->lock);

  while (sbuf->count != 0) {
	  pthread_cond_wait(&sbuf->write_go, &sbuf->lock);
  }

  // do the write
  sbuf->buf = val;
  sbuf->count = 1;

  // let the reader know
  pthread_cond_signal(&sbuf->read_go);

  pthread_mutex_unlock(&sbuf->lock);
}


void *reader(void *arg) {
  SBUF *sbuf = (SBUF *)arg;
  int val;
  while (1) {
    val = sbuf_read(sbuf);
    printf("R: %d\n", val);
  } 
  pthread_exit(NULL);
}

void *writer(void *arg) {
  SBUF *sbuf = (SBUF *)arg;
  int i;
  for (i = 0; i < NUM_WRITES; i++) {
    sbuf_write(sbuf, i);
    printf("W: %d\n", i);
  } 
  pthread_exit(NULL);
}

// run reader and writer
int main(int argc, char *argv[]) {
  pthread_t p1, p2;
  SBUF *sbuf = sbuf_create();
  pthread_create(&p1, NULL, reader, (void *)sbuf);
  pthread_create(&p2, NULL, writer, (void *)sbuf);

  // wait for writer to finish, then terminate
  pthread_join(p2, NULL);
}
