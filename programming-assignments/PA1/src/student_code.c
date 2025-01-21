
#include "student_code.h"
#include <string.h>
#include <stdlib.h>

String String__init(char* input_c_str) {
  String new_str;

  // Get size of the input string since we use it a few times throughout
  size_t length_of_string = strlen(input_c_str);

  // Set metadata associated with the string
  new_str.length = length_of_string;
  new_str.capacity = length_of_string + 1;

  // Copy over the data itself
  new_str.data = malloc(new_str.capacity);
  strncpy(new_str.data, input_c_str, new_str.capacity);

  // Return the string
  return new_str;
}

void String__delete(String* str) {
  free(str->data);
}

size_t String__length(const String* str) {
  // todo
}

void String__reserve(String* str, size_t new_capacity) {
  // todo
}

void String__resize(String* str, size_t new_size, const char c) {
  // todo
}

void String__clear(String* str) {
  // todo
}

bool String__empty(String* str) {
  // todo
}

char String__at(String* str, size_t index) {
  // todo
}

char String__back(String* str) {
  // todo
}

char String__front(String* str) {
  // todo
}

void String__append(String* str, const String* str_to_add) {
  // todo
}

void String__push_back(String* str, const char char_to_add) {
  // todo
}

void String__pop_back(String* str) {
  String__resize(str, (str->length - 1), '\0');
}

void String__insert(String* str, const String* str_to_insert, size_t index) {
  // todo
}

void String__erase(String* str, size_t pos, size_t len) {
  // todo
}

void String__replace(String* str, size_t pos, size_t len, const String* str_to_replace_with) {
  // todo
}

void String__swap(String* str1, String* str2) {
  // todo
}


