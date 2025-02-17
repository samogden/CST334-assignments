Test(Functions, is_entry_valid) {
  PageTableEntry pte = 1;
  cr_assert( !is_entry_valid(pte));
  pte = pte | get_mask_single_bit(VALID_BIT);
  cr_assert(is_entry_valid(pte));
}

Test(Functions, is_read_enabled) {
  PageTableEntry pte = 1;
  cr_assert( !is_read_enabled(pte));
  pte = pte | get_mask_single_bit(READ_BIT);
  cr_assert(is_read_enabled(pte));
}

Test(Functions, is_write_enabled) {
  PageTableEntry pte = 1;
  cr_assert( !is_write_enabled(pte));
  pte = pte | get_mask_single_bit(WRITE_BIT);
  cr_assert(is_write_enabled(pte));
}

Test(Functions, is_execute_enabled) {
  PageTableEntry pte = 1;
  cr_assert( !is_execute_enabled(pte));
  pte = pte | get_mask_single_bit(EXEC_BIT);
  cr_assert(is_execute_enabled(pte));
}

Test(Functions, get_vpn_from_va) {
  srand(time(NULL));
  for (int i = 0; i < NUMBER_OF_REPEATS; i++) {
    VirtualAddress va = rand() % (1<<(NUM_VPN_BITS+NUM_OFFSET_BITS));
    cr_assert( get_vpn_from_va(va) == (va >> (NUM_OFFSET_BITS)));
  }
}

Test(Functions, convert_PageTableEntry_to_PFN) {
  srand ( time(NULL) );
  for (int i = 0; i < NUMBER_OF_REPEATS; i++) {
    VirtualAddress addr_to_test = rand() % PAGE_SIZE;
    PageTableEntry pte = (PageTableEntry)addr_to_test
                         | get_mask_single_bit(VALID_BIT)
                         | get_mask_single_bit(READ_BIT)
                         | get_mask_single_bit(WRITE_BIT)
                         | get_mask_single_bit(EXEC_BIT);
    cr_assert( pte != addr_to_test);
    pte = convert_PageTableEntry_to_PFN(pte);
    cr_assert( pte == addr_to_test );
  }
}

Test(Functions, find_free_page) {
  srand ( time(NULL) );
  MMU* m = malloc(sizeof(MMU));
  m->page_used = (bool*)malloc(NUM_FRAMES*sizeof(bool));
  int num_pages_to_preallocate = rand() % (NUM_FRAMES / 2);
  for (int i = 0; i < num_pages_to_preallocate; i++) {
    m->page_used[i] = true;
  }
  cr_assert(find_free_page(*m) == num_pages_to_preallocate);
}



