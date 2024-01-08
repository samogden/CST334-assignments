//
// Created by Sam Ogden on 9/2/23.
//

#include <criterion/criterion.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../src/student_code.h"

TestSuite(Processes, .disabled=false);

Test(Processes, fork_and_return_child) {
    int parent_pid = getpid();
    int child_pid = fork_and_return_child();

    cr_assert(child_pid != parent_pid); // Is it us?
    cr_assert(child_pid == getpid()); // Since we are now the child, check that

    int status;
    pid_t return_pid = waitpid(child_pid, &status, WNOHANG);
    cr_assert(return_pid != -1); // Make sure it ran
}

Test(Processes, fork_and_return_parent) {
    int parent_pid = getpid();
    int child_pid = fork_and_return_parent();

    cr_assert(child_pid != parent_pid); // Is it us?
    cr_assert(child_pid != getpid()); // Since we are now the child, check that

    int status;
    pid_t return_pid = waitpid(child_pid, &status, WNOHANG);
    cr_assert(return_pid != -1); // Make sure it ran
}


Test(Processes, make_exec_call__fully_qualified_no_args) {
    int status;
    int ret_val = make_exec_call("/bin/ls", NULL, &status);
    cr_assert(ret_val == 0);
}

Test(Processes, make_exec_call__fully_qualified_w_args) {
    int status;
    char* args[] =  {"/bin", NULL};
    int ret_val = make_exec_call("/bin/ls", args, &status);
    cr_assert(ret_val == 0);
}

Test(Processes, make_exec_call__unqualified_no_args) {
    int status;
    int ret_val = make_exec_call("ls", NULL, &status);
    cr_assert(ret_val == 0);
}

Test(Processes, make_exec_call__unqualified_w_args) {
    int status;
    char* args[] =  {"/bin", NULL};
    int ret_val = make_exec_call("ls", args, &status);
    cr_assert(ret_val == 0);
}



