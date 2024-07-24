#ifndef STUDENT_CODE_H
#define STUDENT_CODE_H

#include <stdio.h>
#include <stdbool.h>

#define GROUP_MAX_SIZE 50

// Structs
typedef struct Person {
    char first_name[50];
    char last_name[50];
    int age;
} Person;

typedef struct Group {
    void* group_name; // todo: Pick an appropriate type for this!
    void* group_members[GROUP_MAX_SIZE]; // todo: Pick an appropriate type for this!
    void* num_members; // todo: Pick an appropriate type for this!
} Group;

/*
 * String functions
 */

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated.
 * @return The length of the given string
 */
int get_str_length(char* str);

/**
 * Returns a pointer to a new copy of the original string.
 * It **does not** use strcpy or any related function
 * @param str An input string that is null terminated.
 * @return A new char* that contains a copy of the input string str
 */
char* copy_str(char* str);

/**
 * Truncates a string to a the given length of the string excluding the null terminator.
 * If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string that will be modified in-place.
 * @param new_length The target length of the string.
 */
void truncate_string(char* str, int new_length);

/**
 * Converts a given string to all uppercase letters in-place.
 * @param str A null-terminated input string that will be modified in-place
 */
void to_uppercase(char* str);

/**
 * Converts a string to all lowercase letters in-place.
 * @param str A null-terminated input string that will be modified in-place
 */
void to_lowercase(char* str);

/**
 * Finds the index of the first usage of a target character in a null-terminated string.
 * If the character doesn't occur in the string return -1.
 * @param str A null-terminated input string
 * @param target A character to find in str
 * @return The index of the first usage of the target character in the string, or -1 if it doesn't exist in str.
 */
int find_first_index(char* str, char target);

/**
 * Finds the index of the last usage of a target character in a null-terminated string.
 * If the character doesn't occur in the string return -1.
 * @param str A null-terminated input string
 * @param target A character to find in str
 * @return The index of the last usage of the target character in the string, or -1 if it doesn't exist in str.
 */
int find_last_index(char* str, char target);

/*
 * Struct functions
 */

/**
 * Create a new person struct and return the struct
 * Note: See above for struct definition.
 * Note: you may need to use functions in the string.h library.
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */
Person person_make_new(char* first_name, char* last_name, int age);

/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person struct to get the relevant string for
 * @return A string describing the person of the format "First Last (age)"
 */
char* person_to_string(Person person);

/**
 * Creates and returns a new group.
 * Note: See above for struct definition.  Don't forget to update the field types!
 * @param group_name A null-terminated string to name the new group.
 * @return A new Group struct with fields initialized appropriately.
 */
Group group_make_new(char* group_name);

/**
 * Returns the total number of people currently in a group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group.
 */
int num_people_in_group(Group group);

/**
 * Get the number of free spaces remaining in the group.
 * @param group A Group struct that contains some number of people
 * @return The number of spaces that can still be added to the group.
 */
int free_spaces_in_group(Group group);

/**
 * Add a person to the group if possible and return the remaining free spaces in the group.
 * If adding a new member is impossible return -1.
 * Hint: How do we differentiate between two users who happen to have the same exact name and age?
 * Hint: Does this connect to the type of the `members` field?
 * @param group A group struct representing the group to try to add a new member to
 * @param person_to_add The person to add to try to the group
 * @return The number of free spaces after add the new person or -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add); // Reject if group is full

/**
 * Remove a person to the group if possible and return the remaining free spaces in the group.
 * If removing a new member is impossible return -1.
 * @param group A group struct to remove a person from
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove); // Reject if person isn't in group

/*
 * Caesar Cipher
 */
/**
 * Shift a character 'left' by the shift amount.
 *  e.g. 'a' with a shift_size = 1 will become 'z'
 *  Hint: What are generalized implications of the given unit test?
 * @param input_char
 * @param shift_sizev
 */
char shift_left(char input_char, int shift_size);

/**
 * Shift a character 'right' by the shift amount.
 *  e.g. 'z' with a shift_size = 1 will become 'a'
 * @param input_char
 * @param shift_size
 * @return char: the shifted character in range [a,z]
 */
char shift_right(char input_char, int shift_size);

/**
 * Encrypts a string using a given shift.
 * @param input_str
 * @param shift_size
 * @return char* string encrypted via caeser cipher
 */
char* encrypt_caesar(char* input_str, int shift_size);

/**
 * Decrypts a string using a given shift.
 * @param input_str
 * @param shift_size
 * @return char* string decrypted via caeser cipher
 */
char* decrypt_caesar(char* input_str, int shift_size);

/*
 * General substitution Cipher
 */
/**
 * Returns true if a given encryption key has a valid decryption key.
 * Hint: if the string 'ab' encodes to `zz` is there any way to reliably decode it?
 * @param encryption_key
 * @return bool: whether the encryption key is reversible
 */
bool is_reversible(int* encryption_key);

/**
 * Generates a decryption key based on the encryption key, if one exists.  Otherwise returns NULL
 * Hint: Look at what the given decryption key you're checking against is, and what is being done to the strings
 * @param encryption_key
 * @return int*: decryption key associated with given encryption key
 */
int* get_decryption_key(int* encryption_key);

/**
 * Takes the input string and the encryption key and encrypts the input string in place
 * @param input_str
 * @param encryption_key
 */
void encrypt_substitution(char* input_str, int* encryption_key);

/**
 * Takes an encrypted input string and a decryption key and decrypts a string in place
 * @param input_str
 * @param decryption_key
 */
void decrypt_substitution(char* input_str, int* decryption_key);


#endif //STUDENT_CODE_H
