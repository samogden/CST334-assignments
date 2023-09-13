//
// Created by Sam Ogden on 9/2/23.
//

#include <criterion/criterion.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../src/student_code.h"


#include "../src/student_code.h"

TestSuite(Syscalls, .disabled=false);

Test(Syscalls, open_file_to_read) {
    remove("/tmp/temp.txt");
    FILE* f_write = fopen("/tmp/temp.txt", "w");
    fprintf(f_write, "hello");
    fclose(f_write);

    FILE* f_read = open_file_to_read("/tmp/temp.txt");
    char read_back[10];
    fgets(read_back, 10, f_read);
    fclose(f_read);
    close(fileno(f_read));

    cr_assert(strcmp(read_back, "hello") == 0);

    remove("/tmp/temp.txt");
}

Test(Syscalls, open_file_to_write) {
    remove("/tmp/temp.txt");

    FILE* f_write = open_file_to_write("/tmp/temp.txt");
    fprintf(f_write, "hello");
    fclose(f_write);

    FILE* f_read = fopen("/tmp/temp.txt", "r");
    char read_back[10];
    fgets(read_back, 10, f_read);
    fclose(f_read);

    cr_assert(strcmp(read_back, "hello") == 0);

    remove("/tmp/temp.txt");
}

Test(Syscalls, open_file_to_readwrite) {
    remove("/tmp/temp.txt");

    FILE* f_write = open_file_to_readwrite("/tmp/temp.txt");
    fprintf(f_write, "hello");
    fclose(f_write);

    FILE* f_read = open_file_to_readwrite("/tmp/temp.txt");
    char read_back[10];
    fgets(read_back, 10, f_read);
    fclose(f_read);

    cr_assert(strcmp(read_back, "hello") == 0);

    remove("/tmp/temp.txt");
}

Test(Syscalls, write_str_to_fid) {
    remove("/tmp/temp.txt");

    FILE* f_write = fopen("/tmp/temp.txt", "r+");
    write_str_to_fid("hello", f_write);
    fclose(f_write);

    FILE* f_read = fopen("/tmp/temp.txt", "r");
    char read_back[10];
    fgets(read_back, 10, f_read);
    fclose(f_read);

    cr_assert(strcmp(read_back, "hello") == 0);

    remove("/tmp/temp.txt");
}

Test(Syscalls, read_str_from_fid) {
    remove("/tmp/temp.txt");

    FILE* f_write = fopen("/tmp/temp.txt", "r+");
    fprintf(f_write, "hello");
    fclose(f_write);

    FILE* f_read = fopen("/tmp/temp.txt", "r");
    char* read_back = malloc(10*sizeof(char));
    read_back = read_str_from_fid(f_read, 10);
    fclose(f_read);

    cr_assert(strcmp(read_back, "hello") == 0);

    remove("/tmp/temp.txt");
}

Test(Syscalls, close_fid) {
    FILE* fid = fopen("/tmp/temp.txt", "r+");
    fprintf(fid, "hello");
    close_fid(fid);
    cr_assert(fprintf(fid, "\n") < 0);
}