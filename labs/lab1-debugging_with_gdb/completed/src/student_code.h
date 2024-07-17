#ifndef PROJECTS_STUDENT_CODE_H
#define PROJECTS_STUDENT_CODE_H

typedef struct Person {
    int age;
    char name[16];
    int favorite_number;
} Person;

/**
 * This function takes in an age, a name, and a favorite number and returns a person
 * @param age integer representing age
 * @param name character string representing name (at most 7 chars long!)
 * @param favorite_number integer representing favorite number
 * @return
 */
Person make_new_person(int age, char* name, int favorite_number);

#endif //PROJECTS_STUDENT_CODE_H
