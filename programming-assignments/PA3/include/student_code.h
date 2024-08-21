  #ifndef __student_code_h__
#define __student_code_h__

#include <stdbool.h>
#include <stddef.h>

#define ERR_OUT_OF_MEMORY  (-1)
#define ERR_BAD_ARGUMENTS  (-2)
#define ERR_SYSCALL_FAILED (-3)
#define ERR_CALL_FAILED    (-4)
#define ERR_UNINITIALIZED   (-5)

// Question: How many bytes is this?
#define MAX_ARENA_SIZE (0x7FFFFFFF)

//Note: size represents the number of bytes available for allocation and does
//not include the header bytes.
typedef struct __node_t {
  size_t size;
  bool is_free;
  struct __node_t *fwd;
  struct __node_t *bwd;
} node_t;

extern int statusno;
extern node_t *_free_list;

// Provided functions
extern int init(size_t size);
extern int destroy();
void print_header(node_t *header);

// Functions to write
/**
 * Starting at free_list, find a chunk that is at least `size` in size
 * @param size - size of requested node
 * @param free_list - start point in the free list
 * @return node_t*: first node in the free list big enough for allocation
 */
node_t* find_first_free_chunk(size_t size, node_t* free_list);

/**
 * Prepare node_to_allocate for allocation by splitting, if necessary, or setting metadata.
 * @param node_to_allocate - the memory chunk to prepare
 * @param size - the size of the requested memory
 */
node_t* split_node(node_t* node_to_allocate, size_t size);

/**
 * Given a pointer to an object to free, returns the associated header containing size
 * @param ptr: pointer to allocated memory
 * @return node_t*: given a pointer to allocated memory, return the address of the header
 */
node_t* get_header(void* ptr);

/**
 * Given two nodes, coalesces them into a single node, or sets a number of errors as appropriate
 * @param front: node_t* first in the list
 * @param back: node_t* second in the list
 */
void coalesce_nodes(node_t* front, node_t* back);

// Full functions
/**
 * Allocates a block of memory of the given size
 * @param size: size of block to allocate
 * @return
 */
extern void* mem_alloc(size_t size);

/**
 * Frees a block of memory pointed to by ptr
 * @param ptr: void* to the memory we want to free
 */
extern void mem_free(void* ptr);

/**
 * Adds a newly freed node to the free list.
 * Note: free list should be sorted by address.
 * @param newly_freed_node
 */
void add_to_free_list(node_t* newly_freed_node, node_t* free_list_head);


#endif
