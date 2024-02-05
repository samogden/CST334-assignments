
#include <criterion/criterion.h>
#include <stdio.h>
#include <time.h>
#include "../src/student_code.h"
#include "../src/defines.h"
#include "../src/memory_management_unit.h"

Test(Functions, is_entry_valid) {
  PageTableEntry pte = 0;
  cr_assert( !is_entry_valid(pte));
  pte = pte | single_bit_mask(VALID_BIT);
  cr_assert(is_entry_valid(pte));
}

Test(Functions, is_read_enabled) {
  PageTableEntry pte = 0;
  cr_assert( !is_read_enabled(pte));
  pte = pte | single_bit_mask(READ_BIT);
  cr_assert(is_read_enabled(pte));
}

Test(Functions, is_write_enabled) {
  PageTableEntry pte = 0;
  cr_assert( !is_write_enabled(pte));
  pte = pte | single_bit_mask(WRITE_BIT);
  cr_assert(is_write_enabled(pte));
}

Test(Functions, is_execute_enabled) {
  PageTableEntry pte = 0;
  cr_assert( !is_execute_enabled(pte));
  pte = pte | single_bit_mask(EXEC_BIT);
  cr_assert(is_execute_enabled(pte));
}

Test(Functions, convert_PageTableEntry_to_PFN) {
  PageTableEntry pte = (PageTableEntry)0b1111;
  pte = pte << (NUM_BITS_IN_BYTE * sizeof(PageTableEntry)-4);
  cr_assert( pte != 0x0);
  pte = convert_PageTableEntry_to_PFN(pte);
  cr_assert( pte == 0x0);
}

Test(Functions, find_free_page) {
  srand ( time(NULL) );
  MMU* m = malloc(sizeof(MMU));
  m->page_used = (bool*)malloc(NUM_FRAMES*sizeof(bool));
  int num_pages_to_preallocate = rand() % (NUM_FRAMES / 2);
  for (int i = 0; i < num_pages_to_preallocate; i++) {
    m->page_used[i] = true;
  }
  cr_assert(find_free_page(*m) == num_pages_to_preallocate);
}



