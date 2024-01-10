
#ifndef PROJECTS_STUDENT_CODE_H
#define PROJECTS_STUDENT_CODE_H

#define GROUP_MAX_SIZE 50

#include "stdio.h"

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
    void* group_name; // todo: Make a field to name the group called "group_name"
    void *group_members[GROUP_MAX_SIZE]; // todo: Make a field to store up to GROUP_MAX_SIZE people called "group_members"
    void* num_members; // todo: Make a field to track how many members we have called "num_members"
} Group;

Person person_make_new(char* first_name, char* last_name, int age);
char* person_to_string(Person person);

Group group_make_new(char* group_name);
int num_people_in_group(Group group);
int free_spaces_in_group(Group group);
int add_person(Group* group, Person* person_to_add); // Reject if group is full
int remove_person(Group* group, Person* person_to_remove); // Reject if person isn't in group

//Processes
int fork_and_return_child();
int fork_and_return_parent();
int make_exec_call(char* program_to_call, char** arguments, int* errno);

// System Calls
FILE* open_file_to_read(char* path_to_file);
FILE* open_file_to_write(char* path_to_file);
FILE* open_file_to_readwrite(char* path_to_file);
void write_str_to_fid(char* str, FILE* fid);
char* read_str_from_fid(FILE* f, int max_chars);
void close_fid(FILE* fid);

#endif //PROJECTS_STUDENT_CODE_H
