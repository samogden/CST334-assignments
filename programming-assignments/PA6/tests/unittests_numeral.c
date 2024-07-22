char* generate_random_identifier(int length) {
  char* str = calloc(length + 1, sizeof(char));
  for (int i = 0; i < length; i++) {
    str[i] = rand() % ('z' - 'a');
    if (rand() % 2 == 0) {
      str[i] += 'a';
    } else {
      str[i] += 'A';
    }
  }
  return str;
}

Test(Numeral, parse_numeral__literal, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    int val = rand();

    // Make a test string that contains just a single random number
    char* test_str = calloc(MAX_STR_LENGTH, sizeof(char));
    sprintf(test_str, "%d", val);

    // Make a tokenizer of the test string
    Tokenizer t = init__tokenizer(test_str);

    // Pass the tokenizer into the numeral parser
    Numeral* n = parse_numeral(&t);

    /*
     * We should now have two things:
     * 1.  A numeral is a valid numeral literal
     * 2. A tokenizer that is now empty
    */

    cr_assert_eq(n->num_type, num_literal);
    cr_assert_eq(n->val, val);
    cr_assert(is_done(t));
  }
}

Test(Numeral, parse_numeral__multiple_inputs, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  char test_str[MAX_STR_LENGTH];
  int vals[NUM_TEST_REPEATS];
  int str_index = 0;

  // First we generate a series of random values and make a string out of them all
  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    vals[i] = rand();
    str_index += sprintf(&test_str[str_index], "%d ", vals[i]);
  }

  // Next, we make a tokenizer out of these values
  Tokenizer t = init__tokenizer(test_str);

  // Then we walk through and parse each one at a time
  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    Numeral* n = parse_numeral(&t);

    // Check that we parsed each appropriately
    cr_assert_eq(n->num_type, num_literal);
    cr_assert_eq(n->val, vals[i]);
  }

  // Check that our tokenizer is now empty
  cr_assert(is_done(t));
}

Test(Numeral, parse_numeral__variable, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    // Generate a random identifier that contains just alpha characters
    char* test_str = generate_random_identifier(1 + (rand() % MAX_IDENTIFIER_LENGTH));

    // Make a tokenizer of the test string
    Tokenizer t = init__tokenizer(test_str);

    // Pass the tokenizer into the numeral parser
    Numeral* n = parse_numeral(&t);

    /*
     * We should now have two things:
     * 1.  A numeral is a valid numeral variable
     * 2. A tokenizer that is now empty
    */
    cr_assert_eq(n->num_type, num_variable);
    cr_assert_str_eq(n->identifier, test_str);
    cr_assert(is_done(t));
  }
}


Test(Numeral, parse_numeral__invalid, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    int val = rand();

    // Make a test string that contains just a single random number
    char* test_str = calloc(MAX_STR_LENGTH, sizeof(char));
    sprintf(test_str, "a%d", val); // Note the pre-pended 'a'!

    // Make a tokenizer of the test string
    Tokenizer t = init__tokenizer(test_str);

    // Pass the tokenizer into the numeral parser
    Numeral* n = parse_numeral(&t);

    /*
     * We should now have two things:
     * 1.  A numeral is just a NULL pointer
     * 2. A tokenizer that hasn't moved forward at all
    */
    cr_assert_null(n);
    cr_assert(!is_done(t));
  }

  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    int val = rand();

    // Make a test string that contains just a single random number
    char* test_str = calloc(MAX_STR_LENGTH, sizeof(char));
    sprintf(test_str, "%da", val); // Note the post-pended 'a'!

    // Make a tokenizer of the test string
    Tokenizer t = init__tokenizer(test_str);

    // Pass the tokenizer into the numeral parser
    Numeral* n = parse_numeral(&t);

    /*
     * We should now have two things:
     * 1.  A numeral is just a NULL pointer
     * 2. A tokenizer that hasn't moved forward at all
    */
    cr_assert_null(n);
    cr_assert(!is_done(t));
  }
}


