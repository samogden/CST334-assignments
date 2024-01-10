#ifndef __student_code_h__
#define __student_code_h__

#include "defines.h"
#include "memory_management_unit.h"

/* Page Helpers */
/**
 * Checks whether the given page table entry represents a valid entry or not.  Note that this is done by checking the leading bits.
 * @param pte
 * @return
 */
bool is_entry_valid(PageTableEntry pte);

/**
 * Checks whether the given page table entry can be read or not.  Note that this is done by checking the leading bits.
 * @param pte
 * @return
 */
bool is_read_enabled(PageTableEntry pte);

/**
 * Checks whether the given page table entry can be written or not.  Note that this is done by checking the leading bits.
 * @param pte
 * @return
 */
bool is_write_enabled(PageTableEntry pte);

/**
 * Checks whether the given page table entry can be read or not.  Note that this is done by checking the leading bits.
 * @param pte
 * @return
 */
bool is_execute_enabled(PageTableEntry pte);

/* MMU Helpers*/
/**
 * Given a page table entry, with metadata bits, remove the metadata bits to leave just the PFN we need to index into the physical memory
 * @param pte
 * @return
 */
PFN convert_PageTableEntry_to_PFN(PageTableEntry pte); // Removes the extra information
/**
 * Search for the next available page frame that we can allocate for a mapped page.
 * @param m
 * @return
 */
PFN find_free_page(MMU m);

/* Page Table Functions */
/**
 * Map a new page into the page page table by finding a free page frame and setting the appropriate metadata.
 * @param m
 * @param vpn
 * @param can_read
 * @param can_write
 * @param can_exec
 */
PFN map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec);

/**
 * Search the page table for the entry related to the given virtual address.
 * @param m
 * @param vpn
 * @return
 */
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VirtualAddress vpn);

/* End to End functions that are the same regardless of MMU type */
/**
 * Given an MMU and a virtual address search for the corresponding page in physical memory.  Note that checks should be done for permissions.
 * @param m
 * @param a
 * @param for_read
 * @param for_write
 * @param for_execute
 * @return
 */
Page* get_page(MMU m, VirtualAddress a, bool for_read, bool for_write, bool for_execute);

/**
 * Write a byte to the given virtual address
 * @param m
 * @param va
 * @param val
 */
void write_byte(MMU m, VirtualAddress va, char val);

/**
 * Read a byte from the given virtual address
 * @param m
 * @param va
 * @return
 */
char read_byte(MMU m, VirtualAddress va);

#endif
