
#include <criterion/criterion.h>
#include <stdio.h>
#include "../src/student_code.h"
#include "../src/defines.h"

#define NUMBER_OF_REPEATS 10

Test(MMU_PageTable, get_pagetableentry__MMU_pagetable) {
  // See the random number
  srand( time(NULL) );

  // Create a new MMU
  MMU m = new__MMU_pagetable();

  // Create the page pointer (aka the page pointer), so we can use it
  m.page_pointer = calloc(NUM_PAGES, sizeof(PageTableEntry));

  // Set all the pages to be their equivalent numbers so we can quickly figure out if we grabbed the right one or not
  for (int i = 0; i < NUM_PAGES; i++) {
    m.page_pointer[i] = i;
  }

  // Pick a few random pages and see if they are the right pages
  for (int i = 0; i < NUMBER_OF_REPEATS; i++) {
    int page_to_test = rand() % NUM_PAGES;
    cr_assert(get_pagetableentry__MMU_pagetable(m, page_to_test) == page_to_test);
  }

  cleanup_MMU(m);
}

Test(MMU_PageTable, map_page__MMU_pagetable) {
  // See the random number
  srand( time(NULL) );

  // Create a new MMU
  MMU m = new__MMU_pagetable();

  // Create the page pointer (aka the page pointer), so we can use it
  m.page_pointer = calloc(NUM_PAGES, sizeof(PageTableEntry));
  m.page_used = calloc(NUM_FRAMES, sizeof(bool));

  for (int i = 0; i < NUMBER_OF_REPEATS; i++) {
    int page_to_test = rand() % NUM_PAGES;

    map_page__MMU_pagetable(
      &m, // The MMU we created
      page_to_test, // The page number we're testing
      page_to_test % 2 % 3, // Something random but repeatable
      page_to_test % 2 % 5, // Something random but repeatable
      page_to_test % 2 % 7 // Something random but repeatable
    );

    PageTableEntry pte = m.page_pointer[page_to_test];

    // Check that the PageTableEntry is pointing to the right place
    cr_assert(
      (get_mask(NUM_PFN_BITS + NUM_OFFSET_BITS) & pte)
      ==
      (i)
    );

    cr_assert(is_entry_valid(pte));
    cr_assert(is_read_enabled(pte) == page_to_test % 2 % 3);
    cr_assert(is_write_enabled(pte) == page_to_test % 2 % 5);
    cr_assert(is_execute_enabled(pte) == page_to_test % 2 % 6);
  }

  cleanup_MMU(m);
}


void write_string(MMU m, VirtualAddress va, char* str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    write_byte(m, va+i, str[i]);
  }
    write_byte(m, va+i, '\0');
}

Test(MMU_PageTable, end_to_end) {

  // Create a new MMU
  MMU m = new__MMU_pagetable();

  for (VPN vpn = 0; vpn < NUM_PAGES ; vpn++) {
    if (vpn == NUM_PAGES - 1) {
      m.map_page(&m, vpn, true, true, true);
    } else {
      m.map_page(&m, vpn, vpn % 2 == 0, vpn % 3 == 0, vpn % 5 == 0);
    }
  }

  VirtualAddress va = ((0b0 << NUM_VPN_BITS)  << NUM_OFFSET_BITS) | 0b0;

  char* str;

  str = "hello";
  write_string(m, va, str);
  cr_assert_str_eq(
    (char*)get_page(m, va, true, false, false),
    str
  );


  str = "hello";
  write_string(m, va, str);
  cr_assert_str_eq(
    (char*)get_page(m, va, true, false, false),
    str
  );
  for (int i = 0; i < strlen(str); i++) {
    cr_assert_eq(
      read_byte(m, va+i),
      str[i]
    );
  }

  va = (((0b1<<NUM_VPN_BITS)-1)<< NUM_OFFSET_BITS) | 0b0;
  str = "bye";
  write_string(m, va, str);
  cr_assert_str_eq(
    (char*)get_page(m, va, true, false, false),
    str
  );
  for (int i = 0; i < strlen(str); i++) {
    cr_assert_eq(
      read_byte(m, va+i),
      str[i]
    );
  }

}