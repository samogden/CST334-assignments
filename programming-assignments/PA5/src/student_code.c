#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"
#include "server.h"
#include <stdint.h>

void pass_to_client_handler(void* arg) {
  // todo: Convert this to run multi-threaded
  client_handler(arg);
}

void read_lock(PlayerDatabase* db) {
  // todo
  // Question: What variables do we need to check before we know we can safely read?
}

void read_unlock(PlayerDatabase* db) {
  // todo
}

void write_lock(PlayerDatabase* db) {
  // todo
}

void write_unlock(PlayerDatabase* db) {
  // todo
}

