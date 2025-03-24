typedef struct __lock_t { 
  int flag; 
} lock_t;

void init(lock_t *mutex) {
  mutex->flag = 0;
}

void lock(lock_t *mutex) {
  while (!test_and_set(mutex->flag, 1)) {} 
}

void unlock(lock_t *mutex) {
  mutex->flag = 0;
}
