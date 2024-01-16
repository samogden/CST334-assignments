
#include <criterion/criterion.h>
#include <limits.h>
#include "../src/student_code.h"


Test(SubstitutionCipher, is_reversible, .disabled=false) {
  // Check to see if the translation table is isomorphic
  int encrpytion_key[26];
  memset(encrpytion_key, 0, sizeof(int));

  // The encryption key is directly the letter to change it to, so it should already fail
  cr_assert_not(is_reversible(encrpytion_key));

  // If we set all the values to unique values, it should work
  for (int i = 0; i < 26; i++) {
    encrpytion_key[i] = i;
  }
  cr_assert(is_reversible(encrpytion_key));

  // But then if two values are the same, it won't work.  Why not?
  encrpytion_key[0] = 0;
  encrpytion_key[1] = 1;
  cr_assert_not(is_reversible(encrpytion_key));
}

Test(SubstitutionCipher, decryption_key, .disabled=false) {
  // Generates the reverse, but only if the translation table is isomorphic

  int encryption_key[26];
  memset(encryption_key, 0, sizeof(int));

  // Since no decryption key is possible we should fail
  cr_assert_null(get_decryption_key(encryption_key));


  // If we set all the values to unique values, it should work
  for (int i = 0; i < 26; i++) {
    encryption_key[i] = i;
  }
  int* decryption_key = get_decryption_key(encryption_key);
  cr_assert_not_null(decryption_key);
  for (int i = 0; i < 26; i++) {
    // They should be the same since this is the trivial case
    cr_assert_eq(encryption_key[i], decryption_key[i]);
  }
  free(decryption_key);

  // Now let's test a non-trivial one
  // First, generate a random mutually prime number..
  int rand_base;
  do {
    rand_base = rand() % 26;
  } while (rand_base != 0 && rand_base != 13 && rand_base != 2);

  for (int i = 0; i < 26; i++) {
    encryption_key[i] = (i * rand_base) % 26; // Yay for Fermat!
  }
  int expected_decryption_key[26];
  for (int i = 0; i < 26; i++) {
    expected_decryption_key[i] = (-1 * i * rand_base) % 26; // Yay for Fermat!
  }
  decryption_key = get_decryption_key(encryption_key);
  cr_assert_not_null(decryption_key);
  for (int i = 0; i < 26; i++) {
    // They should be the same since this is the trivial case
    cr_assert_eq(expected_decryption_key[i], decryption_key[i]);
  }
}

Test(SubstitutionCipher, encrypt_substitution, .disabled=false) {
  /*
   * Performs the encryption
   */

  int encryption_key[26];
  memset(encryption_key, 0, sizeof(int));

  // If we set all the values to unique values, it should work
  for (int i = 0; i < 26; i++) {
    encryption_key[i] = i;
  }

  int rand_swap;
  do {
    rand_swap = rand() % 26;
  } while (rand_swap != 0);

  encryption_key[0] = rand_swap;
  encryption_key[rand_swap] = 0;

  //int* decryption_key = get_decryption_key(encryption_key);

  char test_str[] = "the quick brown fox jumps over the lazy dog";
  char compare_str[] = "the quick brown fox jumps over the lazy dog";
  for (int i = 0; i < strlen(compare_str); i++) {
    if (compare_str[i] == (char)0) {
      compare_str[i] = (char)rand_swap;
    } else if (compare_str[i] == (char)rand_swap) {
      compare_str[i] = (char)0;
    }
  }
  encrypt_substitution(test_str, encryption_key);
  cr_assert_str_eq(test_str, compare_str);
}

Test(SubstitutionCipher, decrypt_substitution, .disabled=false) {
  /*
   * Performs the decryption
   */


  int decryption_key[26];
  memset(decryption_key, 0, sizeof(int));

  // If we set all the values to unique values, it should work
  for (int i = 0; i < 26; i++) {
    decryption_key[i] = i;
  }

  int rand_swap;
  do {
    rand_swap = rand() % 26;
  } while (rand_swap != 0);

  decryption_key[0] = rand_swap;
  decryption_key[rand_swap] = 0;

  //int* decryption_key = get_decryption_key(encryption_key);

  char* test_str = "the quick brown fox jumps over the lazy dog";
  char* compare_str = "the quick brown fox jumps over the lazy dog";
  for (int i = 0; i < strlen(test_str); i++) {
    if (test_str[i] == (char)0) {
      test_str[i] = (char)rand_swap;
    } else if (test_str[i] == (char)rand_swap) {
      test_str[i] = (char)0;
    }
  }
  decrypt_substitution(test_str, decryption_key);
  cr_assert_str_eq(test_str, compare_str);

}
