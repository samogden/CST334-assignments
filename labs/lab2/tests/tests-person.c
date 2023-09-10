#include <criterion/criterion.h>
#include "../src/student_code.h"

TestSuite(Person, .disabled=false);

Test(Person, make_new_person, .disabled=false) {
    // First we make a person that fits expectations
    Person p1 = make_new_person(27, "Doug", 42);

    //Next, we test to make sure it worked correctly
    cr_assert(p1.age == 27); // Test age
    cr_assert(strcmp(p1.name, "Doug") == 0); // Note that we use the strcmp function
    cr_assert(p1.favorite_number == 42); // Test favorite number

    // Next we poke around at our expectations a bit
    Person p2 = make_new_person(27, "Douglas A", 42);

    //Next, we test to make sure it worked correctly
    cr_assert(p2.age == 27); // Test age
    cr_assert(strcmp(p2.name, "Douglas A") == 0); // Note that we use the strcmp function
    cr_assert(p2.favorite_number == 42); // Test favorite number
}


Test(Person, make_new_person_badly, .disabled=false) {
    // Next we poke around at our expectations a bit
    Person p2 = make_new_person(27, "Douglas Adams", 42);

    //Next, we test to make sure it worked correctly
    cr_assert(p2.age == 27); // Test age
    cr_assert(strcmp(p2.name, "Douglas Adams") == 0); // Note that we use the strcmp function
    cr_assert(p2.favorite_number == 42); // Test favorite number
}
