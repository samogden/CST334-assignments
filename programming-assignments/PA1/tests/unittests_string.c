Test(String, String__init_0, .disabled=false) {
  char* test_c_string = "Hello";

  String test_str = String__init(test_c_string);

  cr_assert(strlen(test_c_string) == test_str.length);
  cr_assert_str_eq(test_c_string, test_str.data);
}

Test(String, String__length_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  cr_assert(strlen(test_c_string) == test_str.length);
  cr_assert(strlen(test_c_string) == String__length(&test_str));
}


Test(String, String__resize_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  /*
   * There are two cases to check
   * 1. n is smaller than the current length
   * 2. n is greater than the current length and c is specified
   *
   * Let's test these in the order 2, 1 because that's easiest from a testing standpoint
   *
   */


  size_t original_string_length = strlen(test_c_string); // Get the original length
  cr_assert(strlen(test_str.data) == original_string_length); // Double check that the string was copied correctly
  cr_assert(test_str.data[original_string_length+1] == '\0'); // Make sure the string is terminated correctly

  // Make modification #2 outlined above -- make it longer with a specified character
  String__resize(&test_str, original_string_length+2, '!');
  cr_assert(strlen(test_str.data) == (original_string_length+2)); // Check that the string is now longer
  cr_assert(test_str.data[original_string_length+0] == '!'); // Make sure characters were added appropriately
  cr_assert(test_str.data[original_string_length+1] == '!');
  cr_assert(test_str.data[original_string_length+2] == '\0'); // Make sure the string is terminated correctly

  // Make modification #1 outlined above -- make it shorter than the current length
  String__resize(&test_str, original_string_length-1, '!');
  cr_assert(strlen(test_str.data) == (original_string_length-1)); // Check that the string is now longer
  cr_assert(test_str.data[original_string_length] == '\0'); // Make sure the string is terminated correctly
  cr_assert(test_str.data[original_string_length+1] == '\0'); // Make sure that the old characters were "zero"d out
  cr_assert(test_str.data[original_string_length+2] == '\0'); // Make sure that the old characters were "zero"d out

}

Test(String, String__clear_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  // Gather data
  size_t starting_size = String__length(&test_str);

  // Make sure the string is non-empty before we begin
  cr_assert_neq(0, starting_size);

  // Run the test function
  String__clear(&test_str);

  // Check that it's now empty
  cr_assert_eq(0, strlen(test_str.data));
  cr_assert_eq(0, String__length(&test_str));
  cr_assert_neq(starting_size, String__length(&test_str));

}

Test(String, String__empty_0, .disabled=false) {
  char* test_c_string1 = "Hello";
  String test_str1 = String__init(test_c_string1);

  // Check that it is not empty
  cr_expect_not(String__empty(&test_str1));

  char* test_c_string2 = "";
  String test_str2 = String__init(test_c_string2);

  // Check that it is empty
  cr_assert(String__empty(&test_str2));


}

Test(String, String__at_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  // For each character in the input check that it's the same as in the output
  for (int i = 0; i < strlen(test_c_string); i++) {
    cr_assert_eq(test_c_string[i], String__at(&test_str, i));
  }

}

Test(String, String__back_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  cr_assert_eq(
    String__back(&test_str),
    'o' // Hardcoded for the test
  );
}

Test(String, String__front_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  cr_assert_eq(
    String__front(&test_str),
    'H' // Hardcoded for the test
  );
}

Test(String, String__append_0, .disabled=false) {
  char* test_c_string_1 = "Hello";
  String test_str_1 = String__init(test_c_string_1);

  char* test_c_string_2 = "Goodbye";
  String test_str_2 = String__init(test_c_string_2);

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str_1.data) == strlen(test_c_string_1));
  cr_expect(String__length(&test_str_1) == strlen(test_c_string_1));

  /*
   * Operation to test
   */
  String__append(&test_str_1, &test_str_2);

  /*
   * Post-checks
   */
  // Check to see if the lengths make sense
  cr_assert(
    strlen(test_str_1.data)
    ==
    (strlen(test_c_string_1) + strlen(test_c_string_2)),
    "Mismatch of post-copy lengths"
  );
  cr_assert(
    String__length(&test_str_1)
    ==
    (strlen(test_c_string_1) + strlen(test_c_string_2)),
    "Mismatch of post-copy lengths"
  );
  // Check if the characters were copied right
  for (int i = 0; i < strlen(test_c_string_1); i++) {
    cr_assert_eq(test_str_1.data[i], test_c_string_1[i], "Mismatch of copied characters in first string");
  }
  for (int i = 0; i < strlen(test_c_string_2); i++) {
    cr_assert_eq(test_str_1.data[i+strlen(test_c_string_1)], test_c_string_2[i], "Mismatch of copied characters in appended string");
  }
}

Test(String, String__push_back_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  char test_char = '!';

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str.data) == strlen(test_c_string));
  cr_expect(String__length(&test_str) == strlen(test_c_string));

  /*
   * Operation to test
   */
  String__push_back(&test_str, test_char);

  /*
   * Post-checks
   */

  // Check that length makes sense
  cr_assert(strlen(test_str.data) == (strlen(test_c_string) + 1));
  cr_assert(String__length(&test_str) == (strlen(test_c_string) + 1));

  // Check if the characters were left intact
  for (int i = 0; i < strlen(test_c_string); i++) {
    cr_assert_eq(test_str.data[i], test_c_string[i], "Mismatch of copied characters in first string");
  }

  // Check that letter was appended
  cr_assert(test_str.data[strlen(test_c_string)] == test_char);

}

Test(String, String__pop_back_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str.data) == strlen(test_c_string));
  cr_expect(String__length(&test_str) == strlen(test_c_string));

  /*
   * Operation to test
   */
  String__pop_back(&test_str);

  /*
   * Post-checks
   */

  // Check that length makes sense
  cr_assert(strlen(test_str.data) == (strlen(test_c_string) - 1));
  cr_assert(String__length(&test_str) == (strlen(test_c_string) - 1));

  // Check if the characters were left intact
  for (int i = 0; i < strlen(test_c_string) - 1; i++) {
    cr_assert_eq(test_str.data[i], test_c_string[i], "Mismatch of copied characters in string");
  }

}

Test(String, String__insert_0, .disabled=false) {
  char* test_c_string_1 = "Hello";
  String test_str_1 = String__init(test_c_string_1);

  char* test_c_string_2 = "Goodbye";
  String test_str_2 = String__init(test_c_string_2);

  int insert_offset = 1;

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str_1.data) == strlen(test_c_string_1));
  cr_expect(String__length(&test_str_1) == strlen(test_c_string_1));

  /*
   * Operation to test
   */
  String__insert(&test_str_1, &test_str_2, insert_offset);

  /*
   * Post-checks
   */
  // Check to see if the lengths make sense
  cr_assert(
    strlen(test_str_1.data)
    ==
    (strlen(test_c_string_1) + strlen(test_c_string_2)),
    "Mismatch of post-copy lengths"
  );
  cr_assert(
    String__length(&test_str_1)
    ==
    (strlen(test_c_string_1) + strlen(test_c_string_2)),
    "Mismatch of post-copy lengths"
  );

  // Check if the characters were copied right
  int output_index = 0;
  // First, check that the pre-insert offset letters are correct
  for (int input_index = 0; input_index < insert_offset; input_index++, output_index++) {
    cr_assert_eq(
      test_c_string_1[input_index],
      test_str_1.data[output_index]
    );
  }
  // Next, check that the 2nd string was inserted properly
  for (int input_index = 0; input_index < strlen(test_c_string_2); input_index++, output_index++) {
    cr_assert_eq(
      test_c_string_2[input_index],
      test_str_1.data[output_index]
    );
  }
  // Finally, check that the rest of the 1st string was copied
  for (int input_index = insert_offset; input_index < strlen(test_c_string_1); input_index++, output_index++) {
    cr_assert_eq(
      test_c_string_1[input_index],
      test_str_1.data[output_index]
    );
  }
}

Test(String, String__erase_0, .disabled=false) {
  char* test_c_string = "Hello";
  String test_str = String__init(test_c_string);

  int erase_offset = 1;
  int erase_length = 2;

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str.data) == strlen(test_c_string));
  cr_expect(String__length(&test_str) == strlen(test_c_string));

  /*
   * Operation to test
   */
  String__erase(&test_str, erase_offset, erase_length);

  /*
   * Post-checks
   */
  // Check to see if the lengths make sense
  cr_assert(
    strlen(test_str.data)
    ==
    (strlen(test_c_string) - erase_length),
    "Incorrect post-erase length"
  );
  cr_assert(
    String__length(&test_str)
    ==
    (strlen(test_c_string) - erase_length),
    "Incorrect post-erase length"
  );

  // Check if the characters were copied right
  int output_index = 0;
  // Check each letter of the output
  for (int input_index = 0; input_index < strlen(test_c_string); input_index++) {
    // Check if we are in characters that were erased, and if so skip them on the input
    if (erase_offset <= input_index && input_index < (erase_offset + erase_length)) {
      continue;
    }
    cr_assert_eq(
      test_c_string[input_index],
      test_str.data[output_index]
    );
    output_index++;
  }
}

Test(String, String__replace_0, .disabled=false) {
  char* test_c_string_1 = "Hello";
  String test_str_1 = String__init(test_c_string_1);

  char* test_c_string_2 = "Goodbye";
  String test_str_2 = String__init(test_c_string_2);

  int replacement_offset = 1;
  int replacement_length = 2;

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str_1.data) == strlen(test_c_string_1));
  cr_expect(String__length(&test_str_1) == strlen(test_c_string_1));

  /*
   * Operation to test
   */
  String__replace(&test_str_1, replacement_offset, replacement_length, &test_str_2);

  // String should now be "HGoodByelo"

  /*
   * Post-checks
   */
  // Check to see if the lengths make sense
  cr_assert(
    strlen(test_str_1.data)
    ==
    (strlen(test_c_string_1) - replacement_length + strlen(test_c_string_2)),
    "Incorrect post-erase length"
  );
  cr_assert(
    String__length(&test_str_1)
    ==
    (strlen(test_c_string_1) - replacement_length + String__length(&test_str_2)),
    "Incorrect post-erase length"
  );

  // Check if the characters were copied right
  int output_index = 0;
  // First, check that the pre-insert offset letters are correct
  for (int input_index = 0; input_index < replacement_offset; input_index++, output_index++) {
    cr_assert_eq(
      test_c_string_1[input_index],
      test_str_1.data[output_index]
    );
  }
  // Next, check that the 2nd string was inserted properly
  for (int input_index = 0; input_index < strlen(test_c_string_2); input_index++, output_index++) {
    cr_assert_eq(
      test_c_string_2[input_index],
      test_str_1.data[output_index]
    );
  }
  // Finally, check that the rest of the 1st string was copied
  for (int input_index = (replacement_offset + replacement_length); input_index < strlen(test_c_string_1); input_index++, output_index++) {
    cr_assert_eq(
      test_c_string_1[input_index],
      test_str_1.data[output_index]
    );
  }

}

Test(String, String__swap_0, .disabled=false) {
  char* test_c_string_1 = "Hello";
  String test_str_1 = String__init(test_c_string_1);

  char* test_c_string_2 = "Goodbye";
  String test_str_2 = String__init(test_c_string_2);

  /*
   * Pre-checks
   */
  cr_expect(strlen(test_str_1.data) == strlen(test_c_string_1));
  cr_expect(String__length(&test_str_1) == strlen(test_c_string_1));
  cr_expect_str_eq(test_str_1.data, test_c_string_1);

  cr_expect(strlen(test_str_2.data) == strlen(test_c_string_2));
  cr_expect(String__length(&test_str_2) == strlen(test_c_string_2));
  cr_expect_str_eq(test_str_2.data, test_c_string_2);

  /*
   * Operation to test
   */
  String__swap(&test_str_1, &test_str_2);

  /*
   * Post-checks
   */
  // Check to make sure that lengths make sense for having been swapped
  cr_assert(strlen(test_str_1.data) == strlen(test_c_string_2));
  cr_assert(String__length(&test_str_1) == strlen(test_c_string_2));
  cr_assert(strlen(test_str_2.data) == strlen(test_c_string_1));
  cr_assert(String__length(&test_str_2) == strlen(test_c_string_1));

  // Check to make sure that the contents make sense post-swap
  cr_assert_str_eq(test_str_1.data, test_c_string_2);
  cr_assert_str_eq(test_str_2.data, test_c_string_1);

}

