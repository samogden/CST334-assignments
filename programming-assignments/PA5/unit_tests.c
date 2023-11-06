//
// Created by Sam Ogden on 9/2/23.
//



#include <criterion/criterion.h>

#include "tests/unittests_locks.c"
#include "tests/unittests_conditions.c"
#include "tests/unittests_server.c"



#include <pthread.h>

TestSuite(Locks, .disabled=false);
TestSuite(Conditions, .disabled=false);
TestSuite(Server, .disabled=false);

