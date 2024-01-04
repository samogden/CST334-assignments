#ifndef MEMORY_MANAGEMENT_UNIT_H
#define MEMORY_MANAGEMENT_UNIT_H

#include "defines.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct MMU MMU;
typedef struct MMU {
  //void* mmu;
  PageTableEntry* page_pointer;
  char* physical_memory;
  bool* page_used;

  PageTableEntry (*get_pagetableentry)(MMU mmu, VPN);
  PFN (*map_page)(MMU* mmu, VPN vpn, bool can_read, bool can_write, bool can_exec);
} MMU;


// MMU Object Functions
MMU new__MMU_pagetable();
void cleanup_MMU(MMU m);


/* General Helpers */
AddressMask get_mask(unsigned int num_bits);
AddressMask single_bit_mask(unsigned int bit_to_mask);
bool is_bit_set(PageTableEntry pte, unsigned int bit_number);

#endif //MEMORY_MANAGEMENT_UNIT_H
