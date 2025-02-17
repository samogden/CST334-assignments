void* get_three_nodes() {
  void *memory = malloc(3 * sizeof(node_t));
  node_t* node0;
  node_t* node1;
  node_t* node2;

  node0 = memory;
  node1 = memory + sizeof(node_t);
  node2 = memory + 2 * sizeof(node_t);

  node0->size = 0;
  node0->is_free = true;
  node0->fwd = node1;
  node0->bwd = NULL;

  node1->size = 0;
  node1->is_free = true;
  node1->fwd = node2;
  node1->bwd = node0;

  node2->size = 0;
  node2->is_free = true;
  node2->fwd = NULL;
  node2->bwd = node1;

  return memory;
}


Test(Functions, get_header) {
  char* base = malloc(1);
  cr_assert(get_header(base) == (void*)base - sizeof(node_t));
  free(base);
}

Test(Functions, coalesce_nodes__coalesce_first) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  // Run the test
  size_t orig_size = node0->size;
  coalesce_nodes(node0, node1);
  cr_assert(node0->size == orig_size + sizeof(node_t));
  cr_assert(node0->fwd == node2);
  cr_assert(node0->bwd == NULL);

  // Release memory after we're done
  free(memory);

  // Question:  Why don't I need to free the individual nodes?
}

Test(Functions, coalesce_nodes__coalesce_last) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  // Run the test
  size_t orig_size = node1->size;
  coalesce_nodes(node1, node2);
  cr_assert(node1->size == orig_size + sizeof(node_t));
  cr_assert(node1->fwd == NULL);
  cr_assert(node1->bwd == node0);

  // Release memory after we're done
  free(memory);
}

Test(Functions, coalesce_nodes__check_null) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  // Check whether inputting null does nothing but sets statusno
  coalesce_nodes(node1, NULL);
  cr_assert(statusno == ERR_BAD_ARGUMENTS); // Use the errors from student_code.h, not the raw numbers!!
  cr_assert(node1->size == 0);
  cr_assert(node1->is_free == true);
  cr_assert(node1->fwd == node2);
  cr_assert(node1->bwd == node0);

  coalesce_nodes(NULL, node1);
  cr_assert(statusno == ERR_BAD_ARGUMENTS); // Use the errors from student_code.h, not the raw numbers!!
  cr_assert(node1->size == 0);
  cr_assert(node1->is_free == true);
  cr_assert(node1->fwd == node2);
  cr_assert(node1->bwd == node0);

  // Release memory after we're done
  free(memory);
}

Test(Functions, coalesce_nodes__check_order) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  // Check whether inputting in wrong order does nothing but sets statusno
  coalesce_nodes(node1, node0);
  cr_assert(statusno == ERR_BAD_ARGUMENTS); // Use the errors from student_code.h, not the raw numbers!!

  cr_assert(node0->size == 0);
  cr_assert(node0->is_free == true);
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);

  cr_assert(node1->size == 0);
  cr_assert(node1->is_free == true);
  cr_assert(node1->fwd == node2);
  cr_assert(node1->bwd == node0);

  // Release memory after we're done
  free(memory);
}

Test(Functions, coalesce_nodes__check_free) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  node1->is_free = false;

  // Check whether inputting is_free is checked and sets statusno
  coalesce_nodes(node0, node1);
  cr_assert(statusno == ERR_CALL_FAILED); // Use the errors from student_code.h, not the raw numbers!!

  cr_assert(node0->size == 0);
  cr_assert(node0->is_free == true);
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);

  cr_assert(node1->size == 0);
  cr_assert(node1->is_free == false);
  cr_assert(node1->fwd == node2);
  cr_assert(node1->bwd == node0);

  statusno = 0;
  coalesce_nodes(node1, node2);
  cr_assert(statusno == ERR_CALL_FAILED); // Use the errors from student_code.h, not the raw numbers!!

  cr_assert(node1->size == 0);
  cr_assert(node1->is_free == false);
  cr_assert(node1->fwd == node2);
  cr_assert(node1->bwd == node0);

  cr_assert(node2->size == 0);
  cr_assert(node2->is_free == true);
  cr_assert(node2->fwd == NULL);
  cr_assert(node2->bwd == node1);

  // Release memory after we're done
  free(memory);
}

Test(Functions, find_first_free_chunk__0bytes) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  node0->size = 0;
  node1->size = 1;
  node2->size = sizeof(node_t) + 1;

  node_t* chunk = find_first_free_chunk(0, node0);
  cr_assert(chunk == node0);

  free(memory);
}

Test(Functions, find_first_free_chunk__1bytes) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  node0->size = 0;
  node1->size = 1;
  node2->size = sizeof(node_t) + 1;

  node_t* chunk = find_first_free_chunk(1, node0);
  cr_assert(chunk == node1);

  free(memory);
}

Test(Functions, find_first_free_chunk__1bytes_notfree) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  node0->size = 0;
  node1->size = 1;
  node1->is_free = false;
  node2->size = sizeof(node_t) + 1;

  node_t* chunk = find_first_free_chunk(1, node0);
  cr_assert(chunk == node2);

  free(memory);
}

Test(Functions, find_first_free_chunk__2bytes) {
  void* memory = get_three_nodes();
  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + sizeof(node_t));
  node_t* node2 = (node_t*)(memory + 2 * sizeof(node_t));

  node0->size = 0;
  node1->size = 1;
  node2->size = sizeof(node_t) + 1;

  node_t* chunk = find_first_free_chunk(2, node0);
  cr_assert(chunk == node2);

  free(memory);
}

Test(Functions, split_node__same_size) {
  void* memory = malloc(3 * sizeof(node_t));

  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + 2*sizeof(node_t));

  node0->size = 0;
  node0->is_free = true;
  node0->fwd = node1;
  node0->bwd = NULL;

  node1->size = 0;
  node1->is_free = true;
  node1->fwd = NULL;
  node1->bwd = node0;

  split_node(node0, 0);
  cr_assert(node0->size == 0);
  cr_assert(node0->is_free == false);
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);

  free(memory);
}

Test(Functions, split_node__too_small_to_split) {
  void* memory = malloc(3 * sizeof(node_t));

  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + 2*sizeof(node_t));

  node0->size = sizeof(node_t)-1;
  node0->is_free = true;
  node0->fwd = node1;
  node0->bwd = NULL;

  node1->size = 0;
  node1->is_free = true;
  node1->fwd = NULL;
  node1->bwd = node0;

  split_node(node0, 0);
  cr_assert(node0->size == sizeof(node_t)-1);
  cr_assert(node0->is_free == false);
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);

  free(memory);
}


Test(Functions, split_node__big_enough_to_split1) {
  void* memory = malloc(3 * sizeof(node_t));

  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + 2*sizeof(node_t));

  node0->size = sizeof(node_t);
  node0->is_free = true;
  node0->fwd = node1;
  node0->bwd = NULL;

  node1->size = 0;
  node1->is_free = true;
  node1->fwd = NULL;
  node1->bwd = node0;

  log_debug("split_node: pre\n");
  node_t* new_node = split_node(node0, 0);
  log_debug("split_node: post\n");

  log_debug("split_node: testing\n");
  cr_assert(new_node->size == 0);
  log_debug("split_node: testing 1\n");
  cr_assert(new_node->is_free == true);
  cr_assert(new_node->fwd == node1);
  cr_assert(new_node->bwd == NULL);

  cr_assert(node0->size == 0);
  cr_assert(node0->is_free == false);
  cr_assert(node0->fwd == NULL);
  cr_assert(node0->bwd == NULL);

  free(memory);
}


Test(Functions, split_node__big_enough_to_split2) {
  void* memory = malloc(3 * sizeof(node_t) + 1);

  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)(memory + 2*sizeof(node_t)) + 1;


  node0->size = sizeof(node_t) + 1;
  node0->is_free = true;
  node0->fwd = node1;
  node0->bwd = NULL;

  node1->size = 0;
  node1->is_free = true;
  node1->fwd = NULL;
  node1->bwd = node0;

  node_t* new_node = split_node(node0, 1);
  // node_t* new_node = node0->fwd;

  cr_assert(new_node->size == 0);
  cr_assert(new_node->is_free == true);
  cr_assert(new_node->fwd == node1);
  cr_assert(new_node->bwd == NULL);

  cr_assert(node0->size == 1);
  cr_assert(node0->is_free == false);
  cr_assert(node0->fwd == NULL);
  cr_assert(node0->bwd == NULL);

  free(memory);
}

Test(Functions, add_to_free_list__no_free_list) {
  // Note: Although we init, this is a bit of a hack since we aren't actually putting things in the arena
  init(sizeof(node_t));
  void* memory = malloc(sizeof(node_t));
  _free_list = NULL;

  node_t* node0 = (node_t*)memory;
  node0->size = 0;
  node0->fwd = NULL;
  node0->bwd = NULL;
  node0->is_free = false;

  add_to_free_list(node0, _free_list);

  cr_assert(node0->size == 0); // This shouldn't change
  cr_assert_null(node0->fwd); // This should be updated if it were set to something before
  cr_assert_null(node0->bwd); // This should be updated if it were set to something before
  cr_assert_not(node0->is_free); // This isn't touched here

  cr_assert(_free_list == node0);

}

Test(Functions, add_to_free_list__free_list_head) {
  // Note: Although we init, this is a bit of a hack since we aren't actually putting things in the arena
  init(2*sizeof(node_t));
  void* memory = malloc(2*sizeof(node_t));
  _free_list = NULL;

  // This node is allocated
  node_t* node0 = (node_t*)memory;
  node0->size = 0;
  node0->fwd = NULL;
  node0->bwd = NULL;
  node0->is_free = false;

  // This node is unallocated
  node_t* node1 = (node_t*)memory + 1;
  node1->size = 0;
  node1->fwd = NULL;
  node1->bwd = NULL;
  node1->is_free = true;
  // Set the freelist to this node
  _free_list = node1;

  add_to_free_list(node0, _free_list);

  cr_assert(node0->size == 0); // This shouldn't change
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);
  cr_assert( ! node0->is_free); // This isn't touched here

  cr_assert(node1->size == 0); // This shouldn't change
  cr_assert(node1->fwd == NULL);
  cr_assert(node1->bwd == node0);
  cr_assert(node1->is_free); // This isn't touched here

  cr_assert(_free_list == node0);
}

Test(Functions, add_to_free_list__free_list_tail) {
  // Note: Although we init, this is a bit of a hack since we aren't actually putting things in the arena
  init(2*sizeof(node_t));
  void* memory = malloc(2*sizeof(node_t));
  _free_list = NULL;

  // This node is unallocated
  node_t* node0 = (node_t*)memory;
  node0->size = 0;
  node0->fwd = NULL;
  node0->bwd = NULL;
  node0->is_free = true;
  // Set the freelist to this node
  _free_list = node0;

  // This node isnallocated
  node_t* node1 = (node_t*)memory + 1;
  node1->size = 0;
  node1->fwd = NULL;
  node1->bwd = NULL;
  node1->is_free = false;

  add_to_free_list(node1, _free_list);

  cr_assert(node0->size == 0); // This shouldn't change
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);
  cr_assert(node0->is_free); // This isn't touched here

  cr_assert(node1->size == 0); // This shouldn't change
  cr_assert(node1->fwd == NULL);
  cr_assert(node1->bwd == node0);
  cr_assert( ! node1->is_free); // This isn't touched here

  cr_assert(_free_list == node0);
}


Test(Functions, add_to_free_list__free_list_middle) {
  // Note: Although we init, this is a bit of a hack since we aren't actually putting things in the arena
  init(3*sizeof(node_t));
  void* memory = malloc(3*sizeof(node_t));
  _free_list = NULL;

  node_t* node0 = (node_t*)memory;
  node_t* node1 = (node_t*)memory + 1;
  node_t* node2 = (node_t*)memory + 2;

  // This node is unallocated
  node0->size = 0;
  node0->fwd = node2;
  node0->bwd = NULL;
  node0->is_free = true;
  // Set the freelist to this node
  _free_list = node0;

  // This node isnallocated
  node1->size = 0;
  node1->fwd = NULL;
  node1->bwd = NULL;
  node1->is_free = false;

  // This node is unallocated
  node2->size = 0;
  node2->fwd = NULL;
  node2->bwd = node0;
  node2->is_free = true;

  add_to_free_list(node1, _free_list);

  cr_assert(node0->size == 0); // This shouldn't change
  cr_assert(node0->fwd == node1);
  cr_assert(node0->bwd == NULL);
  cr_assert(node0->is_free); // This isn't touched here

  cr_assert(node1->size == 0); // This shouldn't change
  cr_assert(node1->fwd == node2);
  cr_assert(node1->bwd == node0);
  cr_assert( ! node1->is_free); // This isn't touched here

  cr_assert(node2->size == 0); // This shouldn't change
  cr_assert(node2->fwd == NULL);
  cr_assert(node2->bwd == node1);
  cr_assert(node2->is_free); // This isn't touched here

  cr_assert(_free_list == node0);
}
