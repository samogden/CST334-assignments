
#include <criterion/criterion.h>
#include <limits.h>
#include "../src/student_code.h"


#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include "../src/student_code.h"


Test(Free, test_free_basic){
  int size;
  int page_size = getpagesize();
  void *buff;
  node_t *header;

  init(page_size);
  size = page_size - sizeof(node_t);
  buff = mem_alloc(size);
  header = (node_t *)(buff - sizeof(node_t));

  cr_assert(header->is_free == 0);
  mem_free(buff);
  cr_assert(header->is_free == 1);
  cr_assert(header->size == size);

  destroy();
}

Test(Free, test_free_coalescing_case1){
  int size, size2, size3;
  int page_size = getpagesize();
  void *buff, *buff2, *buff3;
  node_t *header, *header2, *header3;

  init(page_size);

  size=64;
  size2=128;
  //Have the third allocation fill up the rest of the arena
  size3=page_size - size - size2 - sizeof(node_t)*3;

  //Case 1: Combine prev, current, next
  buff = mem_alloc(size);
  buff2 = mem_alloc(size2);
  buff3 = mem_alloc(size3);

  cr_assert(buff != NULL);
  cr_assert(buff2 != NULL);
  cr_assert(buff3 != NULL);

  header = ((void*)buff) - sizeof(node_t);
  header2 = ((void*)buff2) - sizeof(node_t);
  header3 = ((void*)buff3) - sizeof(node_t);

  cr_assert(header->is_free == 0);
  cr_assert(header2->is_free == 0);
  cr_assert(header3->is_free == 0);

  mem_free(buff);
  mem_free(buff3);

  cr_assert(header->is_free = 1);
  cr_assert(header3->is_free = 1);

  cr_assert(header->size == size);
  cr_assert(header3->size == size3);

  //this should cause coalescing.
  mem_free(buff2);

  //The coalesced node header should reside at the start of the
  //arena (i.e., where header points)

  cr_assert(header->size == page_size - sizeof(node_t));
  cr_assert(header->bwd == NULL);
  cr_assert(header->fwd == NULL);

  destroy();
}

Test(Free, test_free_coalescing_case2){
  int size, size2;
  int page_size = getpagesize();
  void *buff, *buff2;
  node_t *header, *header2;


  init(page_size);

  size=64;
  //Have this allocation fill up the rest of the arena
  size2=page_size - size - sizeof(node_t)*2;

  buff = mem_alloc(size);
  buff2 = mem_alloc(size2);

  cr_assert(buff != NULL);
  cr_assert(buff2 != NULL);

  header = ((void*)buff) - sizeof(node_t);
  header2 = ((void*)buff2) - sizeof(node_t);

  cr_assert(header->is_free == 0);
  cr_assert(header2->is_free == 0);

  mem_free(buff);
  cr_assert(header->is_free = 1);
  cr_assert(header->size == size);

  //this should cause coalescing.
  mem_free(buff2);

  //The coalesced node header should reside at the start of the
  //arena (i.e., where header points)

  cr_assert(header->size == page_size - sizeof(node_t));
  cr_assert(header->bwd == NULL);
  cr_assert(header->fwd == NULL);

  destroy();
}

Test(Free, test_free_coalescing_case3){
  int size, size2;
  int page_size = getpagesize();
  void *buff, *buff2;
  node_t *header, *header2;

  init(page_size);

  size=64;
  //Have this allocation fill up the rest of the arena
  size2=page_size - size - sizeof(node_t)*2;

  buff = mem_alloc(size);
  buff2 = mem_alloc(size2);

  cr_assert(buff != NULL);
  cr_assert(buff2 != NULL);

  header = ((void*)buff) - sizeof(node_t);
  header2 = ((void*)buff2) - sizeof(node_t);

  cr_assert(header->is_free == 0);
  cr_assert(header2->is_free == 0);

  mem_free(buff2);
  cr_assert(header2->is_free = 1);
  cr_assert(header2->size == size2);

  //this should cause coalescing.
  mem_free(buff);

  //The coalesced node header should reside at the start of the
  //arena (i.e., where header points)

  cr_assert(header->size == page_size - sizeof(node_t));
  cr_assert(header->bwd == NULL);
  cr_assert(header->fwd == NULL);

  destroy();
}


Test(Free, test_free_coalescing_chains_fwd){
  int size;
  int page_size = getpagesize();
  void *buff, *buff2, *buff3, *buff4;

  init(page_size);

  size=64;

  buff = mem_alloc(size);
  buff2 = mem_alloc(size);
  buff3 = mem_alloc(size);
  buff4 = mem_alloc(size);

  cr_assert(buff != NULL);
  cr_assert(buff2 != NULL);
  cr_assert(buff3 != NULL);
  cr_assert(buff4 != NULL);

  node_t *header = ((void*)buff) - sizeof(node_t);

  mem_free(buff);
  mem_free(buff2);
  mem_free(buff3);
  mem_free(buff4);

  //check to make sure the above seq. ends with
  //a single free node.
  cr_assert(header->size == page_size - sizeof(node_t));
  cr_assert(header->is_free == 1);
  cr_assert(header->bwd == NULL);
  cr_assert(header->fwd == NULL);

  destroy();
}


Test(Free, test_free_coalescing_chains_bwd){
  int size;
  int page_size = getpagesize();
  void *buff, *buff2, *buff3, *buff4;

  init(page_size);

  size=64;

  buff = mem_alloc(size);
  buff2 = mem_alloc(size);
  buff3 = mem_alloc(size);
  buff4 = mem_alloc(size);

  cr_assert(buff != NULL);
  cr_assert(buff2 != NULL);
  cr_assert(buff3 != NULL);
  cr_assert(buff4 != NULL);

  node_t *header = ((void*)buff) - sizeof(node_t);

  mem_free(buff4);
  mem_free(buff3);
  mem_free(buff2);
  mem_free(buff);

  //check to make sure the above seq. ends with
  //a single free node.
  cr_assert(header->size == page_size - sizeof(node_t));
  cr_assert(header->is_free == 1);
  cr_assert(header->bwd == NULL);
  cr_assert(header->fwd == NULL);

  destroy();
}
