
#include <criterion/criterion.h>
#include <limits.h>
#include "../src/student_code.h"

#include <stdio.h>
#include <unistd.h>

Test(Alloc, test_allocation_basic) {
  int size = 0;
  int page_size = getpagesize();
  void *buff, *buff2 = NULL;

  buff = mem_alloc(page_size);
  cr_assert(statusno == ERR_UNINITIALIZED);
  cr_assert(buff == NULL);

  // Allocation not possible because we didn't account for the header which is
  // also placed in the arena and takes of sizeof(node_t) bytes.
  init(page_size);
  buff = mem_alloc(page_size);
  cr_assert(statusno == ERR_OUT_OF_MEMORY);
  cr_assert(buff == NULL);

  size = page_size-sizeof(node_t);
  buff = mem_alloc(size);
  cr_assert(buff != NULL);

  // Check that we can write to the allocated memory
  memset(buff, 'a', size);
  cr_assert(((char *)buff)[0] == 'a' && ((char *)buff)[size-1] == 'a');

  //This allocation should fail because the previous allocation used all of
  //the remaining space.
  buff2 = mem_alloc(1);
  cr_assert(buff2 == NULL);
  cr_assert(statusno == ERR_OUT_OF_MEMORY);

  destroy();
}




Test(Alloc, test_allocationfree_placement){
  int size = 0;
  int page_size = getpagesize();
  void *buff, *buff2,  *buff3;
  node_t *header = NULL;

  // Test: Create two allocations.
  // Free first allocation but leave the second allocation in place.
  // Create third allocation an Ensure that the
  // third allocation is placed in the first free chunk
  init(page_size);

  size = 32;
  buff = mem_alloc(size);
  cr_assert(buff != NULL);
  memset(buff, 'a', size);

  header = (node_t *)(buff - sizeof(node_t));

  //This checks that the header for the first allocation is placed
  //at the start of a page boundary. If this check fails, then the
  //first header is not placed at the start of the arena.
  cr_assert(((unsigned long)header & 0xFFF) == 0);

  buff2 = mem_alloc(size);
  buff2 = buff2;

  mem_free(buff);

  //Next allocation should be in same place as the first allocation
  buff3 = mem_alloc(size);
  cr_assert(buff3 == buff);
  //The characters from the previous memset should also be there
  cr_assert(((char *)buff)[0] == 'a' && ((char *)buff)[size-1] == 'a');

  destroy();
}



Test(Alloc, test_allocation_withsplits){
  int size =0;
  int page_size = getpagesize();
  void *buff = NULL, *buff2 = NULL;
  node_t *header = NULL, *header2 = NULL;

  // Test: First allocation causes split. Check that the header is in the
  // correct place, has the correct field values, and that chunks were split
  // correctly
  init(page_size);
  buff = mem_alloc(64);
  cr_assert(buff != NULL);

  header = (node_t *)(buff - sizeof(node_t));
  cr_assert(header->size == 64);
  cr_assert(header->bwd == NULL);
  cr_assert(header->is_free == 0);
  cr_assert(header->fwd == ((void*)header)+sizeof(node_t)+64);

  node_t *next = header->fwd;

  cr_assert(next->fwd == NULL);
  cr_assert(next->bwd == header);
  cr_assert(next->size == page_size-64-(sizeof(node_t)*2));
  cr_assert(next->is_free == 1);

  // Test: Second allocation uses up remaining free space. Check that
  // the allocation is in the correct place and has the correct field values.
  size = page_size - 64 - (sizeof(node_t) * 2);
  buff2 = mem_alloc(size);

  header2 = (node_t *)(buff2 - sizeof(node_t));

  cr_assert(header2 == next);
  cr_assert(header2->size == size);
  cr_assert(header2->is_free == 0);
  cr_assert(header2->fwd == NULL);
  cr_assert(header2->bwd == header);

  destroy();

	// Test: Only split if the process of splitting would leaves
	// enough room for another chunk.
	init(page_size);
  buff = mem_alloc(64);
	//This should leave 10 bytes remaining in the arena
  size = page_size - 64 - (sizeof(node_t) * 2) - 10;
	buff2 = mem_alloc(size);

  header2 = (node_t *)(buff2 - sizeof(node_t));

  cr_assert(header2->size == size + 10);
  cr_assert(header2->fwd == NULL);

  destroy();
}


