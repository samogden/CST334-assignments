#ifndef __student_code_h__
#define __student_code_h__

#include <stdbool.h>

#define ERR_OUT_OF_MEMORY  (-1)
#define ERR_BAD_ARGUMENTS  (-2)
#define ERR_SYSCALL_FAILED (-3)
#define ERR_CALL_FAILED    (-4)
#define ERR_UNINITIALIZED   (-5)

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
node_t * find_first_free_chunk(size_t size, node_t* starting_node);
void split_node(node_t* node, size_t size);

node_t* get_header(void* ptr);
void coalesce_nodes(node_t* front, node_t* back);

// Full functions
extern void* mem_alloc(size_t size);
extern void mem_free(void *ptr);




#endif
