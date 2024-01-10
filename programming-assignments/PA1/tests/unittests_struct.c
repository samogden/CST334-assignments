

#include <criterion/criterion.h>

#include "../src/student_code.h"


Test(Struct, person_make_new, .disabled=false) {
    Person p = person_make_new("Sam", "Ogden", 35);
    cr_assert(strcmp(p.first_name, "Sam") == 0);
    cr_assert(strcmp(p.last_name, "Ogden") == 0);
    cr_assert(p.age = 35);
}

Test(Struct, person_to_string, .disabled=false) {
    Person p = person_make_new("Sam", "Ogden", 35);
    cr_assert(strcmp(person_to_string(p), "Sam Ogden (35)") == 0);
}

Test(Struct, group_make_new, .disabled=false) {
    Group g = group_make_new("totally not cyborgs");
    cr_assert(strcmp(g.group_name, "totally not cyborgs") == 0);
    cr_assert(sizeof(g.group_members) == 50*sizeof(Person*));
    cr_assert(g.num_members == 0);
}

Test(Struct, num_people_in_group, .disabled=false) {
    Group g = group_make_new("totally not cyborgs");
    cr_assert(num_people_in_group(g) == 0);
}

Test(Struct, free_spaces_in_group, .disabled=false) {
    Group g = group_make_new("totally not cyborgs");
    cr_assert(free_spaces_in_group(g) == GROUP_MAX_SIZE);
}

Test(Struct, add_person, .disabled=false) {
    Group g = group_make_new("totally not cyborgs");
    Person p1 = person_make_new("Sam", "Ogden", 35);
    Person p2 = person_make_new("Andrew", "Human", 42);

    add_person(&g, &p1);
    cr_assert(g.num_members == 1);
    cr_assert(g.group_members[0] == &p1);

    add_person(&g, &p2);
    cr_assert(g.num_members == 2);
    cr_assert(g.group_members[0] == &p1);
    cr_assert(g.group_members[1] == &p2);

    add_person(&g, &p1);
    add_person(&g, &p2);
    cr_assert(g.num_members == 2);
}

Test(Struct, remove_person, .disabled=false) {
    Group g = group_make_new("totally not cyborgs");
    Person p1 = person_make_new("Sam", "Ogden", 35);
    Person p2 = person_make_new("Andrew", "Human", 42);

    add_person(&g, &p1);
    add_person(&g, &p2);
    cr_assert(g.num_members == 2);
    cr_assert(g.group_members[0] == &p1);
    cr_assert(g.group_members[1] == &p2);

    remove_person(&g, &p1);
    cr_assert(g.num_members == 1);
    cr_assert(g.group_members[0] == &p2);
}