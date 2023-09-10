#include <string.h>
#include "student_code.h"


/***********
 * Persons *
 ***********/

Person make_new_person(int age, char* name, int favorite_number) {
    Person p;
    p.age = age;
    strcpy(p.name, name);
    p.favorite_number = favorite_number;
    return p;
}
