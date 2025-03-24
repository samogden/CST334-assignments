
#include "src/student_code.h"
#include "src/server.h"

int main() {
  setup();
  pthread_t* t = make_request_async("do_slow_thing 2");
  char* return_val;
  pthread_join(*t, (void**)&return_val);
  printf("Returned: \"%s\"\n", return_val);
  teardown();
  return 0;
}
