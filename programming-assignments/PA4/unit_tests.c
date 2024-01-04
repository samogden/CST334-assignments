//
// Created by Sam Ogden on 9/2/23.
//


#include <criterion/criterion.h>

#include "tests/unittests_functions.c"
#include "tests/unittests_alloc.c"
#include "tests/unittests_free.c"


TestSuite(Functions, .disabled=false);
TestSuite(Alloc, .disabled=false);
TestSuite(Free, .disabled=false);

