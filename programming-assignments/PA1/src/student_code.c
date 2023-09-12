//
// Created by Sam Ogden on 8/28/23.
//

#include "student_code.h"


/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The lenght of the inpurt string
 */
int get_str_length(char* str) {
    // todo
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    return -1;
}

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
char* copy_str(char* str) {
    // todo
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    return NULL;
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    // todo
}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
    // todo
}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
    // todo
}

/**
 * Finds the index of the first usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the first usage of the target character in the string
 */
int find_first_index(char* str, char target) {
    // todo
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    return -1;
}

/**
 * Finds the index of the last usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the last usage of the target character in the string
 */
int find_last_index(char* str, char target) {
    // todo
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    return -1;
}


/**************
 * Structures *
 **************/
/**
 * Create a new person object and return the object
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */
Person person_make_new(char* first_name, char* last_name, int age) {
    // todo
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {
    // todo
    // hint: sprintf
    return NULL;
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminuated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
    // todo
}

/**
 * A function to find the total number of people in the group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group
 */
int num_people_in_group(Group group) {
    // todo
    return -1;
}
/**
 * Get the number of free spaces remaining in the group
 * @param group A Group struct that contains some number of people
 * @return The number of free spaces in the group
 */
int free_spaces_in_group(Group group) {
    // todo
    return -1;
}

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
    // todo
    return -1;
}

/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
    // todo
    return -1;
}

/*************
 * Processes *
 *************/
/**
 * Fork off a process and return the child's PID *from the child process*
 * @return the PID of the child process
 */
int fork_and_return_child() {
    // todo
    /*
     * Question:
     * Is this even possible?
     * If it is then make it so, if it isn't then write a quick paragraph telling me why it isn't possible using the ideas of `fork(...)` discussed in class
     *    and then ignore the unit test failing (by setting .disable)
     */
    return -1;
}

/**
 * Fork off a process and return the child's PID *from the parent process*
 * @return the PID of the child process
 */
int fork_and_return_parent() {
    // todo
    return -1;
}

/**
 * Fork a process and then call exec to run the program
 * @param program_to_call Name of the program to call
 * @param arguments Arguments to pass to the program we're calling
 * @param errno Error code if necessary.  Set to 0 for success, 1 for failure to fork, 2 for failure to exec
 * @return Exit code of exec call if errno == 0, else -1
 */
int make_exec_call(char* program_to_call, char** arguments, int* errno) {
    // todo
    return -1;
}

/****************
 * System Calls *
 ****************/

/**
 * Print a call using system calls.  Note: You should not use printf or any variation for this, just the `syscall(...)` function
 * @param str The null-terminated string to print
 */
void print_string(char* str) {
    // todo
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
}

/**
 * Open a file to read using the `open(...)` call in C
 * @param path_to_file The null terminated path to the file to open
 * @return A FILE point object
 */
FILE* open_file_to_read(char* path_to_file) {
    // todo
    // hint: https://stackoverflow.com/a/1658517
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
    return NULL;
}

/**
 * Open a file to write using the `open(...)` call in C
 * @param path_to_file The null terminated path to the file to open
 * @return A FILE point object
 */
FILE* open_file_to_write(char* path_to_file) {
    // todo
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
    return NULL;
}

/**
 * Open a file to read or write using the `open(...)` call in C
 * @param path_to_file The null terminated path to the file to open
 * @return A FILE point object
 */
FILE* open_file_to_readwrite(char* path_to_file) {
    // todo
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
    return NULL;
}

/**
 * Given a FID, write the given string to the fid using the `write(...)` system call
 * @param str A null-terminuated string
 * @param fid A FILE file descriptor
 */
void write_str_to_fid(char* str, FILE* f) {
    // todo
    // hint: https://linuxhint.com/write-system-call-c/
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
}

/**
 * Given a file descriptor, read a newline-terminated string from a file
 * @param f A FILE file descriptor
 * @param max_chars Maximum characters to read
 * @return
 */
char* read_str_from_fid(FILE* f, int max_chars) {
    // todo
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
    return NULL;
}

/**
 * Given a file descriptor, close the FID
 * @param f The file descriptor to close using the `close(...)` system call
 */
void close_fid(FILE* f) {
    // todo
    // Note: You cannot use any of the functions in unistd.h that begin with 'f' for this assignment!  Instead make sure you use `open(...)` and `close(...)` and similar functions!
    // Failure to do so will result in a 0 for this function!
}
