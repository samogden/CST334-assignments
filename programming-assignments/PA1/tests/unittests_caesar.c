
#include <criterion/criterion.h>
#include <limits.h>
#include "../src/student_code.h"


Test(CaesarCipher, shift_left, .disabled=false) {
  cr_assert_eq(shift_left('a', 0), 'a');
  cr_assert_eq(shift_left('a', 1), 'z');
  cr_assert_eq(shift_left('a', 2), 'y');
  cr_assert_eq(shift_left('a', 25), 'b');
  cr_assert_eq(shift_left('A', 0), 'a');
}

Test(CaesarCipher, shift_right, .disabled=false) {
  cr_assert_eq(shift_right('a', 0), 'a');
  cr_assert_eq(shift_right('a', 1), 'b');
  cr_assert_eq(shift_right('a', 25), 'z');
  cr_assert_eq(shift_right('A', 0), 'a');
}

Test(CaesarCipher, encrypt_caesar, .disabled=false) {
  char* test_str = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";

  cr_assert_str_eq(
    encrypt_caesar(test_str, 0),
    "if he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out."
  );

  cr_assert_str_eq(
    encrypt_caesar(test_str, 3),
    "fc eb exa xkvqefkd zlkcfabkqfxi ql pxv, eb tolqb fq fk zfmebo, qexq fp, yv pl zexkdfkd qeb loabo lc qeb ibqqbop lc qeb ximexybq, qexq klq x tloa zlria yb jxab lrq."
  );
}

Test(CaesarCipher, decrypt_caesar, .disabled=false) {
  char* test_str = "if he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";

  cr_assert_str_eq(
    decrypt_caesar(test_str, 0),
    "if he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out."
  );

  cr_assert_str_eq(
    decrypt_caesar(
    "fc eb exa xkvqefkd zlkcfabkqfxi ql pxv, eb tolqb fq fk zfmebo, qexq fp, yv pl zexkdfkd qeb loabo lc qeb ibqqbop lc qeb ximexybq, qexq klq x tloa zlria yb jxab lrq.",
    3),
    test_str
  );
}