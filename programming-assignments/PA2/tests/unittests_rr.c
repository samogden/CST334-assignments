Test(RR, pri0) {
  PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
  PROCESS_LIST *pl = create_process_list();
  add_process_to_tail(pl, p0);

  PROCESS *selected = rr_process_selector(pl);
  cr_assert(selected == p0);
}

Test(RR, pri0_pri1) {
  PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
  PROCESS *p1 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS_LIST *pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);
  p1->last_run = 1.0;
  PROCESS *selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 2.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p1);
  selected->last_run = 3.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p0);
}

Test(RR, pri1_pri0) {
  PROCESS *p0 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS *p1 = create_process(1.0f, 0.0f, 0.0f);
  PROCESS_LIST *pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);
  p1->last_run = 1.0;

  PROCESS *selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 2.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p1);
  selected->last_run = 3.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 4.0;

}

Test(RR, pri0_pri1_pri1) {
  PROCESS *p0 = create_process(1.0f, 0.0f, 0.0f);
  PROCESS *p1 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS *p2 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS_LIST *pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);
  add_process_to_tail(pl, p2);
  p2->last_run = 1.0;

  PROCESS *selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 2.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p1);
  selected->last_run = 3.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p2);
  selected->last_run = 4.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 5.0;
}

Test(RR, pri1_pri0_pri1) {
  PROCESS *p0 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS *p1 = create_process(1.0f, 0.0f, 0.0f);
  PROCESS *p2 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS_LIST *pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);
  add_process_to_tail(pl, p2);
  p2->last_run = 1.0;

  PROCESS *selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 2.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p1);
  selected->last_run = 3.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p2);
  selected->last_run = 4.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 5.0;

}

Test(RR, pri1_pri1_pri0) {
  PROCESS *p0 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS *p1 = create_process(1.0f, 1.0f, 0.0f);
  PROCESS *p2 = create_process(1.0f, 0.0f, 0.0f);
  PROCESS_LIST *pl = create_process_list();
  add_process_to_tail(pl, p0);
  add_process_to_tail(pl, p1);
  add_process_to_tail(pl, p2);
  p2->last_run = 1.0;

  PROCESS *selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 2.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p1);
  selected->last_run = 3.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p2);
  selected->last_run = 4.0;

  selected = rr_process_selector(pl);
  cr_assert(selected == p0);
  selected->last_run = 5.0;

}