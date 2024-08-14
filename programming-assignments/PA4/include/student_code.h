#ifndef __student_code_h__
#define __student_code_h__

#include "defines.h"
#include "memory_management_unit.h"

/* Page Helpers */
/**
 * Checks whether the given page table entry represents a valid entry or not.
 * Note: metadata is stored in the MSB places
 * @param pte: page table entry to check
 * @return bool: whether the valid bit is set or not
 */
bool is_entry_valid(PageTableEntry pte);

/**
 * Checks whether the given page table entry can be read or not.
 * Note: metadata is stored in the MSB places
 * @param pte: page table entry to check
 * @return bool: whether the read bit is set or not
 */
bool is_read_enabled(PageTableEntry pte);

/**
 * Checks whether the given page table entry can be written or not.
 * Note: metadata is stored in the MSB places
 * @param pte: page table entry to check
 * @return bool: whether the write bit is set or not
 */
bool is_write_enabled(PageTableEntry pte);

/**
 * Checks whether the given page table entry can be executed or not.
 * Note: metadata is stored in the MSB places
 * @param pte: page table entry to check
 * @return bool: whether the execute bit is set or not
 */
bool is_execute_enabled(PageTableEntry pte);

/**
 * Given a VirtualAddress, return the VPN associated with it
 * @param va
 * @return (VPN) of the the Virtual Address
 */
VPN get_vpn_from_va(VirtualAddress va);

/* MMU Helpers*/
/**
 * Given a page table entry, with metadata bits, remove the metadata bits to leave just the PFN
 * @param pte: page table entry to convert
 * @return PFN: the Page Frame Number that we will use to index into physical memory.
 */
PFN convert_PageTableEntry_to_PFN(PageTableEntry pte);

/**
 * Search for the next available physical page that we can allocate for a new virtual page.
 * @param m: (MMU) the MMU that we are doing mapping withint
 * @return (PFN): the free PFN that we can allocate to the new virtual page.
 */
PFN find_free_page(MMU m);

/* Page Table Functions */
/**
 * Map a new page into the page table by finding a free page frame and setting the appropriate metadata.
 * @param m (MMU): MMU in which we are mapping memory
 * @param vpn (VPN): VPN that are are trying to map into memory
 * @param can_read (bool): bool for read-access
 * @param can_write (bool): bool for write-access
 * @param can_exec (bool): bool for execute-access
 * @return (PFN): the newly mapped PFN
 */
PFN map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec);

/**
 * Get the PageTableEntry associated with a given VPN.
 * @param m (MMU): MMU in which we are maping memory
 * @param vpn (VPN): VPN to search the page table for
 * @return (PageTableEntry) : entry in m corresponding to vpn
 */
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VirtualAddress vpn);

/* End to End functions that are the same regardless of MMU type */
/**
 * Given an MMU and a virtual address search for the corresponding page in physical memory.  Note that checks should be done for permissions.
 * @param m (MMU): MMU in which we are mapping memory
 * @param va (VirtualAddress): Virtual address we want to access
 * @param for_read (bool): are we trying to read
 * @param for_write (bool): are we trying to write
 * @param for_execute (bool): are we trying to execute
 * @return (Page*) : base address of page we are searching for
 */
Page* get_page(MMU m, VirtualAddress va, bool for_read, bool for_write, bool for_execute);

/**
 * Write a byte to the given virtual address
 * @param m (MMU): MMU in which we are mapping memory
 * @param va (VirtualAddress): Virtual address we want to access
 * @param val
 */
void write_byte(MMU m, VirtualAddress va, char val);

/**
 * Read a byte from the given virtual address
 * @param m  (MMU): MMU in which we are mapping memory
 * @param va (VirtualAddress): Virtual address we want to access
 * @return (char) : character at virtual address va
 */
char read_byte(MMU m, VirtualAddress va);

#endif
