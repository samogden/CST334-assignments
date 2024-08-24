
#include "student_code.h"


/***********
 * Strings *
 ***********/
int get_str_length(char* str) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // Question: How do we know that we've gotten to the end of a c-string?
  return -1;
}

char* copy_str(char* str) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  return "";
}

void truncate_string(char* str, int new_length) {
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  // todo
}

void to_uppercase(char* str) {
  // todo
}

void to_lowercase(char* str) {
  // todo
}

int find_first_index(char* str, char target) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  return -1;
}

int find_last_index(char* str, char target) {
  // todo
  // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
  return -1;
}


/**************
 * Structures *
 **************/
Person person_make_new(char* first_name, char* last_name, int age) {
  Person p = {};
  // todo
  return p;
}

char* person_to_string(Person person) {
  // todo
  // hint: sprintf
  return "";
}

Group group_make_new(char* group_name) {
Group g = {};
  // todo
  return g;
}

int num_people_in_group(Group group) {
  // todo
  return -1;
}

int free_spaces_in_group(Group group) {
  // todo
  return -1;
}

int add_person(Group* group, Person* person_to_add) {
  // todo
  // Question: Say we have already added a person to the group and try to add them again.  What should be we do?  Where can we check what the expected behavior is?
  return -1;
}

int remove_person(Group* group, Person* person_to_remove) {
  // todo
  return -1;
}



/*
 * Caesar Cipher
 */
char shift_left(char input_char, int shift_size) {
  // todo
  return 0;
}

char shift_right(char input_char, int shift_size) {
  // todo
  return 0;
}

char* encrypt_caesar(char* input_str, int shift_size) {
  // todo
  return NULL;
}

char* decrypt_caesar(char* input_str, int shift_size) {
  // todo
  return NULL;
}

/*
 * General substitution Cipher
 */

bool is_reversible(int* encryption_key) {
  // todo
  return false;
}

int* get_decryption_key(int* encryption_key) {
  // todo
  return NULL;
}

void encrypt_substitution(char* input_str, int* encryption_key) {
  // todo
  return;
}

void decrypt_substitution(char* input_str, int* decryption_key) {
  // todo
  return;
}




