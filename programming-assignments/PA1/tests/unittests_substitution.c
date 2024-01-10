
#include <criterion/criterion.h>
#include <limits.h>
#include "../src/student_code.h"


Test(SubstitutionCipher, is_reversible, .disabled=false) {
  // Check to see if the translation table is isomorphic
}

Test(SubstitutionCipher, decryption_key, .disabled=false) {
  // Generates the reverse, but only if the translation table is isomorphic
}

Test(SubstitutionCipher, encrypt_substitution, .disabled=false) {
  // Performs the encryption
}

Test(SubstitutionCipher, decrypt_substitution, .disabled=false) {
  // Performs the decryption
}
