#ifndef DEFINES_H
#define DEFINES_H

#include "stdint.h"
#include "stdbool.h"

// General defines
#define NUM_BITS_IN_BYTE 8

// Add in some flexibility in case we want to change the size of our data structures
#define PAGETABLE_ENTRY_SIZE 8
#if PAGETABLE_ENTRY_SIZE == 8
  #define PAGETABLE_ENTRY_TYPE uint64_t
#elif PAGETABLE_ENTRY_SIZE == 4
  #define PAGETABLE_ENTRY_TYPE uint32_t
#else
  #define PAGETABLE_ENTRY_SIZE 8
  #define PAGETABLE_ENTRY_TYPE uint64_t
#endif

// Core defines -- the rest are largely calculated from ehre
#define NUM_OFFSET_BITS 10
#define NUM_VPN_BITS 12
#define NUM_PFN_BITS 20
#define NUM_METADATA_BITS 4

// Question: Given these definitions, how many bytes will out physical memory be?

// Define some derived types and sizes
#define PAGE_SIZE ((1<<NUM_OFFSET_BITS))
#define NUM_PAGES ((1<<NUM_VPN_BITS))
#define NUM_FRAMES ((1<<NUM_PFN_BITS))
#define PHYSICAL_MEMORY_SIZE ((1<<(NUM_PFN_BITS + NUM_OFFSET_BITS)))
#define PAGE_DIRECTORY_ENTRIES (PAGE_SIZE / (NUM_PAGES * PAGETABLE_ENTRY_SIZE))
//#define PD_VPN_BITS ((NUM_PAGES * PAGETABLE_ENTRY_SIZE) / PAGE_SIZE)
#define PD_VPN_BITS (NUM_VPN_BITS - (NUM_OFFSET_BITS - PAGETABLE_ENTRY_SIZE))

// Define specific bits
#define VALID_BIT (NUM_BITS_IN_BYTE*sizeof(AddressBasis) - 0)
#define READ_BIT (NUM_BITS_IN_BYTE*sizeof(AddressBasis) - 1)
#define WRITE_BIT (NUM_BITS_IN_BYTE*sizeof(AddressBasis) - 2)
#define EXEC_BIT (NUM_BITS_IN_BYTE*sizeof(AddressBasis) - 3)

// Question: Do we need to worry about these metadata bits interfering with our entries?  Why or why not?

// Set up the types that we are using.  Notice that they are all basically the same.
typedef PAGETABLE_ENTRY_TYPE AddressBasis;
typedef AddressBasis AddressMask;
typedef AddressBasis VirtualAddress;
typedef AddressBasis PhysicalAddress;
typedef AddressBasis VPN;
typedef AddressBasis OFFSET;
typedef AddressBasis PFN; // Contains both a valid bit and the PFN

typedef struct Page {
  char data[PAGE_SIZE];
} Page;
typedef Page PageFrame;

// Now rename a few for clarity later on
typedef PFN PageTableEntry;
typedef PageTableEntry PageDirectoryEntry;
typedef Page PageTableChunk;


#endif //DEFINES_H
