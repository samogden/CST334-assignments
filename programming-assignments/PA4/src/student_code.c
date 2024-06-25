#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"



bool is_entry_valid(PageTableEntry pte) {
  // todo;
}

bool is_read_enabled(PageTableEntry pte) {
  // todo
  // Question: Implement this function.  Hint: it can take as little as 1 line.
}

bool is_write_enabled(PageTableEntry pte) {
  // todo
}

bool is_execute_enabled(PageTableEntry pte) {
  // todo
}


PFN find_free_page(MMU m) {
  // todo
}

PFN convert_PageTableEntry_to_PFN(PageTableEntry pte) {
  // todo
}


/*
 * Page Table Functions
 */
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VPN vpn) {
  // todo
}

PFN map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec) {
  // todo
}


/*
 * Page Directory Functions
 */

Page* get_page(MMU m, VirtualAddress va, bool for_read, bool for_write, bool for_execute) {
  // todo
}

char read_byte(MMU m, VirtualAddress va) {
  // todo
}

void write_byte(MMU m, VirtualAddress va, char val) {
  // todo
}
