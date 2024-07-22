Test(Parser, parse_simple__good, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  char* test_str = "1";

  Expression* e = parse(test_str);

  cr_assert_not_null(e);
}

Test(Parser, parse_simple__bad, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  char* test_str = "#";

  Expression* e = parse(test_str);

  cr_assert_null(e);
}

Test(Parser, parse_complex__good, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  char* test_str = "( 1 + 1 )";

  Expression* e = parse(test_str);

  cr_assert_not_null(e);
}

Test(Parser, parse_complex__bad__toolong, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  // Question: Why do we expect this parser to fail?
  char* test_str = "( 1 + 1 + 1 )";

  Expression* e = parse(test_str);

  cr_assert_null(e);
}


Test(Parser, parse_complex__bad__malformed, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  char* test_str = "(1+1)";

  Expression* e = parse(test_str);

  cr_assert_null(e);
}