//
// Created by Sam Ogden on 8/8/23.
//

#include <criterion/criterion.h>

#include "../src/process_scheduling.h"
#include "../src/student_code.h"

TestSuite(PRIORITY, .disabled=false);

Test(PRIORITY, pri0) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);

    PROCESS *selected = priority_process_selector(pl);
    cr_assert(selected == p0);
}

Test(PRIORITY, pri0_pri1) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);

    PROCESS *selected = priority_process_selector(pl);
    cr_assert(selected == p0);
}

Test(PRIORITY, pri1_pri0) {
    PROCESS *p0 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);

    PROCESS *selected = priority_process_selector(pl);
    cr_assert(selected == p1);
}

Test(PRIORITY, pri0_pri1_pri1) {
    PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS *p2 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);
    add_process_to_tail(pl, p2);

    PROCESS *selected = priority_process_selector(pl);
    cr_assert(selected == p0);
}

Test(PRIORITY, pri1_pri0_pri1) {
    PROCESS *p0 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS *p2 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);
    add_process_to_tail(pl, p2);

    PROCESS *selected = priority_process_selector(pl);
    cr_assert(selected == p1);
}

Test(PRIORITY, pri1_pri1_pri0) {
    PROCESS *p0 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS *p1 = create_process(1.0f, 1.0f, 0.0f);
    PROCESS *p2 = create_process(1.0f, 0.0f, 0.0f);
    PROCESS_LIST *pl = create_process_list();
    add_process_to_tail(pl, p0);
    add_process_to_tail(pl, p1);
    add_process_to_tail(pl, p2);

    PROCESS *selected = priority_process_selector(pl);
    cr_assert(selected == p2);
}