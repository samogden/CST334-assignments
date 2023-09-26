//
// Created by Sam Ogden on 9/2/23.
//

#include <criterion/criterion.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../src/process_scheduling.h"
#include "../src/student_code.h"

TestSuite(FIFO, .disabled=false);

Test(FIFO, e0) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);

    PROCESS *selected = fifo_process_selector(pl);
    cr_assert(selected == p0);
}

Test(FIFO, e0_e1) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);

    PROCESS *selected = fifo_process_selector(pl);

    cr_assert(selected == p0);
    cr_assert(selected != p1);
    cr_assert(selected != NULL);
}

Test(FIFO, e1_e0) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);

    PROCESS *selected = fifo_process_selector(pl);

    cr_assert(selected == p1);
}

Test(FIFO, e0_e1_1) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS *p2 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);
    add_process_to_tail(pl, p2);

    PROCESS *selected = fifo_process_selector(pl);
    cr_assert(selected == p0);
}

Test(FIFO, e1_e0_e1) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS *p2 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);
    add_process_to_tail(pl, p2);

    PROCESS *selected = fifo_process_selector(pl);
    cr_assert(selected == p1);
}

Test(FIFO, e1_e1_e0) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 1.0f);
    PROCESS *p2 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);
    add_process_to_tail(pl, p2);

    PROCESS *selected = fifo_process_selector(pl);
    cr_assert(selected == p2);
}