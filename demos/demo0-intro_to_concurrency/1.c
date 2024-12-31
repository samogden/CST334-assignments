#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct __myarg_t {
  int a;
  int b;
} myarg_t;

typedef struct __myreturn_t {
  int rc;
} myreturn_t;

void* mythread(void* arg) {
  myarg_t* m = (myarg_t*) arg;
  printf("%d %d\n", m->a, m->b);
  myreturn_t* r = malloc(sizeof(myreturn_t));
  r->rc = m->a * 3;
  return r;
}

#define NUM_THREADS 10

int main(int argc, char* argv[]) {


  pthread_t p[NUM_THREADS];
  myreturn_t* ret_vals[NUM_THREADS];
  myarg_t args[NUM_THREADS];
  for (int i = 0 ; i < NUM_THREADS; i++) {
    args[i].a = i;
    args[i].b = i*2;
    pthread_create(
      &p[i],
      NULL,
      mythread,
      &args[i]
    );
  }
  for (int i = 0 ; i < NUM_THREADS; i++) {
    pthread_join(p[i], (void*)&ret_vals[i]);
    printf("ret_vals[%d]: %d\n", i, ret_vals[i]->rc);
  }
}
