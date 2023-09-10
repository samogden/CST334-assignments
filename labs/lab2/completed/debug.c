#include "stdio.h"
#include "string.h"
#include "src/student_code.h"

int main() {
    // Next we poke around at our expectations a bit
    Person p2 = make_new_person(27, "Douglas Adams", 42);

    //Next, we test to make sure it worked correctly
    printf("%d\n", (p2.age == 27)); // Test age
    printf("%d\n", (strcmp(p2.name, "Douglas Adams") == 0)); // Note that we use the strcmp function
    printf("%d\n", (p2.favorite_number == 42)); // Test favorite number


    return 0;
}
