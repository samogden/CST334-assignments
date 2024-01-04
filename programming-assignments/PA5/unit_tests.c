//
// Created by Sam Ogden on 9/2/23.
//


#include <criterion/criterion.h>

#include "tests/unittests_functions.c"
#include "tests/unittests_mmu_pagetable.c"

TestSuite(Functions, .disabled=false);
TestSuite(MMU_PageTable, .disabled=false);

