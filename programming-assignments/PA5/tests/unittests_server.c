Test(
  Server,
  is_server_threaded,
  // .init=setup,
  // .fini=teardown,
  .timeout=3,
  .disabled=false
) {

  server_info_t* server_info = setup();
  log_debug("Testing server threading....\n")

  // Question: Why do you think I start counting at t1 here instead of t0?
  client_msg* msg = malloc(sizeof(client_msg));
  msg->port = server_info->port;
  strcpy(msg->msg, "do_slow_thing 2");

  pthread_t* t1 = make_request_async(msg);
  pthread_t* t2 = make_request_async(msg);

  pthread_join(*t1, NULL);
  pthread_join(*t2, NULL);

  teardown(server_info);
}


Test(Server,
 increment_test,
 // .init=setup,
 // .fini=teardown,
 .timeout=(1 + NUM_PLAYS + 6)*TIME_DELAY + 4*TIME_DELAY, // hint: why is this my timeout?
 .disabled=false
 ) {
  server_info_t* server_info = setup();

  log_debug("Testing server increment_test....\n")
  pthread_t* threads[NUM_PLAYS];

  client_msg* addplayer_msg = malloc(sizeof(client_msg));
  addplayer_msg->port = server_info->port;
  strcpy(addplayer_msg->msg, "add_player sam");
  make_request(addplayer_msg);


  client_msg msgs[NUM_PLAYS];
  int high_score = 0;
  int score = 0;
  for (int i = 0; i < NUM_PLAYS; i++) {
    score = (2 * NUM_PLAYS - i);
    msgs[i].port = server_info->port;
    sprintf(msgs[i].msg, "add_player_score sam %d", score);
    if (score > high_score) {
      high_score = score;
    }
    threads[i] = make_request_async(&msgs[i]);
    fsleep(TIME_DELAY / 100.0);
  }
  log_debug("here 2\n")
  for (int i = 0; i < NUM_PLAYS; i++) {
    pthread_join(*threads[i], NULL);
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  char expected_response[100];

  // Used to hold al lthe various back-and-forths
  client_msg* msg = malloc(sizeof(client_msg));
  msg->port = server_info->port;

  strcpy(msg->msg, "get_player_plays sam");
  sprintf(expected_response, "%d", NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  strcpy(msg->msg, "get_player_high_score sam");
  sprintf(expected_response, "%d", high_score);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  strcpy(msg->msg, "get_best_player");
  cr_assert_str_eq(
    (char*)make_request(msg),
    "sam"
    );

  strcpy(msg->msg, "get_num_players");
  cr_assert_str_eq(
    (char*)make_request(msg),
    "1"
    );

  strcpy(msg->msg, "get_highest_score");
  sprintf(expected_response, "%d", 2*NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  strcpy(msg->msg, "get_total_plays");
  sprintf(expected_response, "%d", NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );
  teardown(server_info);
}


Test(
  Server,
  increment_test_two_users,
  // .init=setup,
  // .fini=teardown,
  .timeout=(2 + NUM_PLAYS + 6)*TIME_DELAY + 4*TIME_DELAY, // hint: why is this my timeout?
  .disabled=false
) {
  server_info_t* server_info = setup();

  log_debug("Testing server increment_test_two_users....\n")
  pthread_t* threads[NUM_PLAYS];

  client_msg* addplayer_msg = malloc(sizeof(client_msg));
  addplayer_msg->port = server_info->port;
  strcpy(addplayer_msg->msg, "add_player sam0");
  make_request(addplayer_msg);
  strcpy(addplayer_msg->msg, "add_player sam1");
  make_request(addplayer_msg);

  client_msg msgs[NUM_PLAYS];
  int high_score = 0;
  int score = 0;
  for (int i = 0; i < NUM_PLAYS; i++) {
    msgs[i].port = server_info->port;
    if (i % 2 == 0) {
      score = (2 * NUM_PLAYS - i);
      sprintf(msgs[i].msg, "add_player_score sam0 %d", score);
      // sprintf(msg[i], "add_player_score sam0 %d", score);
    } else {
      score = (2 * NUM_PLAYS + i);
      sprintf(msgs[i].msg, "add_player_score sam1 %d", score);
      // sprintf(msg[i], "add_player_score sam1 %d", score);
    }
    if (score > high_score) {
      high_score = score;
    }
    threads[i] = make_request_async(&msgs[i]);
    fsleep(TIME_DELAY / 100.0);
  }
  for (int i = 0; i < NUM_PLAYS; i++) {
    pthread_join(*threads[i], NULL);
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  char expected_response[100];

  // Used to hold al lthe various back-and-forths
  client_msg* msg = malloc(sizeof(client_msg));
  msg->port = server_info->port;

  // strcpy(msg->msg, "get_player_plays sam");
  // (char*)make_request(msg),

  strcpy(msg->msg, "get_player_plays sam0");
  sprintf(expected_response, "%d", NUM_PLAYS/2);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );
  strcpy(msg->msg, "get_player_plays sam1");
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  strcpy(msg->msg, "get_best_player");
  cr_assert_str_eq(
    (char*)make_request(msg),
    "sam1"
    );

  strcpy(msg->msg, "get_num_players");
  cr_assert_str_eq(
    (char*)make_request(msg),
    "2"
    );

  strcpy(msg->msg, "get_highest_score");
  sprintf(expected_response, "%d", high_score);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  strcpy(msg->msg, "get_total_plays");
  sprintf(expected_response, "%d", NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );
  teardown(server_info);
}




Test(Server,
 increment_test_two_users_mixed_workload,
 // .init=setup,
 // .fini=teardown,
 .timeout=(NUM_PLAYS+5)*TIME_DELAY, // The duration, plus a few extra for the tests below
 .disabled=false
) {

  server_info_t* server_info = setup();

  log_debug("Testing server increment_test_two_users_mixed_workload....\n")
  pthread_t* threads[NUM_PLAYS];

  client_msg* addplayer_msg = malloc(sizeof(client_msg));
  addplayer_msg->port = server_info->port;
  strcpy(addplayer_msg->msg, "add_player sam0");
  make_request(addplayer_msg);
  strcpy(addplayer_msg->msg, "add_player sam1");
  make_request(addplayer_msg);

  double time_start = currentTime();

  client_msg msgs[NUM_PLAYS];
  int high_score_0 = 0;
  int high_score_1 = 0;
  int plays_0 = 0;
  int plays_1 = 0;
  int score = 0;

  for (int i = 0; i < NUM_PLAYS; i++) {
    msgs[i].port = server_info->port;
    int modulo_base = 6;
    if (i % 2 == 0) {
      modulo_base = 4; // Then limit to only read operations
    }
    switch (rand() % modulo_base) {
    case 0:
      sprintf(msgs[i].msg, "get_total_plays");
      break;
    case 1:
      sprintf(msgs[i].msg, "get_best_player");
      break;
    case 2:
      sprintf(msgs[i].msg, "get_player_plays sam0");
      break;
    case 3:
      sprintf(msgs[i].msg, "get_num_players");
      break;
    case 4:
      score = rand() % 1000;
      sprintf(msgs[i].msg, "add_player_score sam0 %d", score);
      plays_0++;
      if (score > high_score_0) {
        high_score_0 = score;
      }
      break;
    case 5:
      score = rand() % 1000;
      sprintf(msgs[i].msg, "add_player_score sam1 %d", score);
      plays_1++;
      if (score > high_score_1) {
        high_score_1 = score;
      }
      break;
    }
    threads[i] = make_request_async(&msgs[i]);
    fsleep(TIME_DELAY / 100.0);
  }
  for (int i = 0; i < NUM_PLAYS; i++) {
    pthread_join(*threads[i], NULL);
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  char expected_response[100];

  // Used to hold al lthe various back-and-forths
  client_msg* msg = malloc(sizeof(client_msg));
  msg->port = server_info->port;

  // strcpy(msg->msg, "get_player_plays sam");
  // (char*)make_request(msg),

  strcpy(msg->msg, "get_player_plays sam0");
  sprintf(expected_response, "%d", plays_0);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );


  strcpy(msg->msg, "get_player_plays sam1");
  sprintf(expected_response, "%d", plays_1);
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  strcpy(msg->msg, "get_num_players");
  cr_assert_str_eq(
    (char*)make_request(msg),
    "2"
    );

  int high_score = (high_score_0 > high_score_1) ? high_score_0 : high_score_1;
  sprintf(expected_response, "%d", high_score);

  strcpy(msg->msg, "get_highest_score");
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  sprintf(expected_response, "%d", plays_0 + plays_1);
  strcpy(msg->msg, "get_total_plays");
  cr_assert_str_eq(
    (char*)make_request(msg),
    expected_response
    );

  double time_end = currentTime();
  log_debug("run time: %f\n", (time_end - time_start));

  teardown(server_info);
}



