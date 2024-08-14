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


/**
 * Function to create a new MMU (memory management unit) struct.
 * @return
 */
MMU MMU__pagetable__init();

/**
 * Releases the memory in an MMU
 * @param m
 */
void MMU_destroy(MMU m);


/* General Helpers */
/**
 * (Helper Function) Gets a mask with the given number of bits set and all others unset.
 * For example, `get_mask(2)` would return 0b11
 * @param num_bits_to_mask
 * @return
 */
AddressMask get_mask(unsigned int num_bits_to_mask);

/**
 * (Helper Function) Get a mask with only a single bit set.
 * For example, `get_mask_single_bit(2)` would return 0b10
 * @param bit_to_mask
 * @return
 */
AddressMask get_mask_single_bit(unsigned int bit_to_mask);

/**
 * (Helper Function) Query whether a particular bit is set.
 * For example, `is_bit_set(0b10, 0)` would be false but `is_bit_set(0b10, 1)` would be true.
 * @param pte
 * @param bit_number
 * @return
 */
bool is_bit_set(PageTableEntry pte, unsigned int bit_number);

#endif //MEMORY_MANAGEMENT_UNIT_H
