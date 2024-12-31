#ifndef STUDENT_CODE_H
#define STUDENT_CODE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct CPP_String {
  char* data;      // Actual character pointer storing data
  size_t length;   // Size of the current string
  size_t capacity; // Size of the underlying buffer
} String;


/**
 * Initilize a new String (CPP_String) strct from a given c-string
 * @param input_c_str
 * @return A new String struct
 */
String String__init(char* input_c_str);

/**
 * Frees components of the String struct
 * @param str
 */
void String__delete(String* str);

/**
 * Gets the length of the given string, excluding null-terminator
 * @param str
 * @return length of given string struct
 */
size_t String__length(const String* str);

/**
 * Gets the capacity of the given String struct, which may be longer than just a single null-terminator
 * @param str
 * @return
 */
size_t String__capacity(const String* str);

/**
 * Increases capacity of given String struct to give new_size, if appropriate, otherwise leaves it untouched.
 * @param str
 * @param new_size
 */
void String__reserve(String* str, size_t new_capacity);

/**
 * Increases the size of the given String struct, repeating with given char is appropriate.
 * @param str
 * @param new_capacity
 * @param c
 */
void String__resize(String* str, size_t new_size, const char c);

/**
 * Clears the given String struct
 * @param str
 */
void String__clear(String* str);

/**
 * Returns true if the string currently has length 0, otherwise false.
 * @param str
 * @return
 */
bool String__empty(String* str);

/**
 * Returns the character at the given index, or the null-terminator ('\0') if index is inappropriate.
 * @param str
 * @param index
 * @return
 */
char String__at(String* str, size_t index);

/**
 * Returns the last non-null-terminator character of the string
 * @param str
 * @return
 */
char String__back(String* str);

/**
 * Returns the first character of the string, or the null-terminator if zero length.
 * @param str
 * @return
 */
char String__front(String* str);

/**
 * Appends contents of str_to_add to str, increasing capacity as necessary.
 * @param str
 * @param str_to_add
 */
void String__append(String* str, const String* str_to_add);

/**
 * Adds char_to_add to the end of given String str, increasing capacity as necessary
 * @param str
 * @param char_to_add
 */
void String__push_back(String* str, const char char_to_add);

/**
 * Removes the last element of String str.
 * @param str
 */
void String__pop_back(String* str);

/**
 * Inserts String str_to_insert into String str starting at location index
 * @param str
 * @param str_to_insert
 * @param index
 */
void String__insert(String* str, const String* str_to_insert, size_t index);

/**
 * Erases a part of String str starting at location pos and going for len.
 * @param str
 * @param pos
 * @param len
 */
void String__erase(String* str, size_t pos, size_t len);

/**
 * Replaces the substring in String str starting at pos and running for len with String str_to_replace_with
 * @param str
 * @param pos
 * @param len
 * @param str_to_replace_with
 */
void String__replace(String* str, size_t pos, size_t len, const String* str_to_replace_with);

/**
 * Swaps the contents of str1 and str2.
 * @param str1
 * @param str2
 */
void String__swap(String* str1, String* str2);

#endif