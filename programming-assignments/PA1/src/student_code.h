
#ifndef PROJECTS_STUDENT_CODE_H
#define PROJECTS_STUDENT_CODE_H

#define GROUP_MAX_SIZE 50

#include "stdio.h"
#include "stdbool.h"

// String Functions
int get_str_length(char* str);
char* copy_str(char* str);
void truncate_string(char* str, int new_length);
void to_uppercase(char* str);
void to_lowercase(char* str);
int find_first_index(char* str, char target);
int find_last_index(char* str, char target);

// Structs
typedef struct Person {
    char first_name[50];
    char last_name[50];
    int age;
} Person;

typedef struct Group {
    // We want a group of up to GROUP_MAX_SIZE, with a count of how many people we have
    void* group_name; // todo: Pick an appropriate type for this!
    void* group_members[GROUP_MAX_SIZE]; // todo: Pick an appropriate type for this!
    void* num_members; // todo: Pick an appropriate type for this!
} Group;

Person person_make_new(char* first_name, char* last_name, int age);
char* person_to_string(Person person);

Group group_make_new(char* group_name);
int num_people_in_group(Group group);
int free_spaces_in_group(Group group);
int add_person(Group* group, Person* person_to_add); // Reject if group is full
int remove_person(Group* group, Person* person_to_remove); // Reject if person isn't in group

/*
 * Caesar Cipher
 */
char shift_left(char input_char, int shift_size);
char shift_right(char input_char, int shift_size);
char* encrypt_caesar(char* input_str, int shift_size);
char* decrypt_caesar(char* input_str, int shift_size);

/*
 * General substitution Cipher
 */

bool is_reversible(int* encryption_key);
int* get_decryption_key(int* encryption_key);
void encrypt_substitution(char* input_str, int* encryption_key);
void decrypt_substitution(char* input_str, int* decryption_key);


#endif //PROJECTS_STUDENT_CODE_H
