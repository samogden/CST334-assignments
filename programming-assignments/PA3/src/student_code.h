#ifndef __student_code_h__
#define __student_code_h__

#include <stdbool.h>

#define ERR_OUT_OF_MEMORY  (-1)
#define ERR_BAD_ARGUMENTS  (-2)
#define ERR_SYSCALL_FAILED (-3)
#define ERR_CALL_FAILED    (-4)
#define ERR_UNINITIALIZED   (-5)

// Question: How many bytes is this?
#define MAX_ARENA_SIZE (0x7FFFFFFF)

extern int statusno;

//Note: size represents the number of bytes available for allocation and does
//not include the header bytes.
typedef struct __node_t {
  size_t size;
  bool is_free;
  struct __node_t *fwd;
  struct __node_t *bwd;
} node_t;

// Provided functions
extern int init(size_t size);
extern int destroy();
void print_header(node_t *header);

// Functions to write
/**
 * Finds the first available free chunk that is big enough to support the requested size allocation.
 * @param size
 * @param starting_node
 * @return
 */
node_t * find_first_free_chunk(size_t size, node_t* starting_node);

/**
 * Takes in the selected chunk of free memory and prepares it for usage, potentially by splitting it up into smaller pieces.
 * @param node -- the chunk to prepare
 * @param size
 */
void split_node(node_t* node, size_t size);

/**
 * Given a pointer to an object to free, returns the associated header containing size
 * @param ptr
 * @return
 */
node_t* get_header(void* ptr);

/**
 * Given two nodes, coalesces them into a single node, or sets a number of errors as appropriate
 * @param front
 * @param back
 */
void coalesce_nodes(node_t* front, node_t* back);

// Full functions
/**
 * Allocates a block of memory of the given size
 * @param size
 * @return
 */
extern void* mem_alloc(size_t size);

/**
 * Frees a block of memory pointed to by ptr
 * @param ptr
 */
extern void mem_free(void *ptr);




#endif
