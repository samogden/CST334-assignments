
#include <criterion/criterion.h>
#include "../src/student_code.h"

#include "../src/server.h"
#include "../src/common.h"


Test(Server, is_server_threaded, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {
  log_debug("Testing server threading....\n")

  // Question: Why do you think I start counting at t1 here instead of t0?
  pthread_t* t1 = make_request_async("do_slow_thing 2");
  pthread_t* t2 = make_request_async("do_slow_thing 2");

  pthread_join(*t1, NULL);
  pthread_join(*t2, NULL);
}


Test(Server,
     increment_test,
     .init=setup,
     .fini=teardown,
     .timeout=NUM_PLAYS*2,
     .disabled=false
       ) {
  log_debug("Testing server increment_test....\n")
  pthread_t* threads[NUM_PLAYS];
  make_request("add_player sam");

  char msg[NUM_PLAYS][100];
  int high_score = 0;
  int score = 0;
  for (int i = 0; i < NUM_PLAYS; i++) {
    score = (2 * NUM_PLAYS - i);
    sprintf(msg[i], "add_player_score sam %d", score);
    if (score > high_score) {
      high_score = score;
    }
    threads[i] = make_request_async(msg[i]);
  }
  for (int i = 0; i < NUM_PLAYS; i++) {
    pthread_join(*threads[i], NULL);
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  char expected_response[100];

  sprintf(expected_response, "%d", NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request("get_player_plays sam"),
    expected_response
  );

  sprintf(expected_response, "%d", high_score);
  cr_assert_str_eq(
    (char*)make_request("get_player_high_score sam"),
    expected_response
  );

  cr_assert_str_eq(
    (char*)make_request("get_best_player"),
    "sam"
  );

  cr_assert_str_eq(
    (char*)make_request("get_num_players"),
    "1"
  );

  sprintf(expected_response, "%d", 2*NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request("get_highest_score"),
    expected_response
  );

  sprintf(expected_response, "%d", NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request("get_total_plays"),
    expected_response
  );
}


Test(Server, increment_test_two_users, .init=setup, .fini=teardown, .timeout=NUM_PLAYS*2*TIME_DELAY, .disabled=false) {
  log_debug("Testing server increment_test_two_users....\n")
  pthread_t* threads[NUM_PLAYS];
  make_request("add_player sam0");
  make_request("add_player sam1");

  char msg[NUM_PLAYS][100];
  int high_score = 0;
  int score = 0;
  for (int i = 0; i < NUM_PLAYS; i++) {
    if (i % 2 == 0) {
      score = (2 * NUM_PLAYS - i);
      sprintf(msg[i], "add_player_score sam0 %d", score);
    } else {
      score = (2 * NUM_PLAYS + i);
      sprintf(msg[i], "add_player_score sam1 %d", score);
    }
    if (score > high_score) {
      high_score = score;
    }
    threads[i] = make_request_async(msg[i]);
  }
  for (int i = 0; i < NUM_PLAYS; i++) {
    pthread_join(*threads[i], NULL);
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  char expected_response[100];

  sprintf(expected_response, "%d", NUM_PLAYS/2);
  cr_assert_str_eq(
    (char*)make_request("get_player_plays sam0"),
    expected_response
  );
  cr_assert_str_eq(
    (char*)make_request("get_player_plays sam1"),
    expected_response
  );

  cr_assert_str_eq(
    (char*)make_request("get_best_player"),
    "sam1"
  );

  cr_assert_str_eq(
    (char*)make_request("get_num_players"),
    "2"
  );

  sprintf(expected_response, "%d", high_score);
  cr_assert_str_eq(
    (char*)make_request("get_highest_score"),
    expected_response
  );

  sprintf(expected_response, "%d", NUM_PLAYS);
  cr_assert_str_eq(
    (char*)make_request("get_total_plays"),
    expected_response
  );
}




Test(Server,
     increment_test_two_users_mixed_workload,
     .init=setup,
     .fini=teardown,
     .timeout=(NUM_PLAYS+5)*TIME_DELAY // The duration, plus a few extra for the tests below
       ) {
  log_debug("Testing server increment_test_two_users_mixed_workload....\n")
  pthread_t* threads[NUM_PLAYS];
  make_request("add_player sam0");
  make_request("add_player sam1");
  double time_start = currentTime();

  char msg[NUM_PLAYS][100];
  int high_score_0 = 0;
  int high_score_1 = 0;
  int plays_0 = 0;
  int plays_1 = 0;
  int score = 0;

  for (int i = 0; i < NUM_PLAYS; i++) {
    switch (rand() % 6) {
      case 0:
        score = rand() % 1000;
        sprintf(msg[i], "add_player_score sam0 %d", score);
        plays_0++;
        if (score > high_score_0) {
          high_score_0 = score;
        }
        break;
      case 1:
        score = rand() % 1000;
        sprintf(msg[i], "add_player_score sam1 %d", score);
        plays_1++;
        if (score > high_score_1) {
          high_score_1 = score;
        }
        break;
      case 2:
        sprintf(msg[i], "get_total_plays");
        break;
      case 3:
        sprintf(msg[i], "get_best_player");
        break;
      case 4:
        sprintf(msg[i], "get_player_plays sam0");
        break;
      case 5:
        sprintf(msg[i], "get_num_players");
        break;
    }
    threads[i] = make_request_async(msg[i]);
  }
  for (int i = 0; i < NUM_PLAYS; i++) {
    pthread_join(*threads[i], NULL);
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  char expected_response[100];

  sprintf(expected_response, "%d", plays_0);
  cr_assert_str_eq(
    (char*)make_request("get_player_plays sam0"),
    expected_response
  );
  sprintf(expected_response, "%d", plays_1);
  cr_assert_str_eq(
    (char*)make_request("get_player_plays sam1"),
    expected_response
  );

  cr_assert_str_eq(
    (char*)make_request("get_num_players"),
    "2"
  );

  int high_score = (high_score_0 > high_score_1) ? high_score_0 : high_score_1;
  sprintf(expected_response, "%d", high_score);
  cr_assert_str_eq(
    (char*)make_request("get_highest_score"),
    expected_response
  );

  sprintf(expected_response, "%d", plays_0 + plays_1);
  cr_assert_str_eq(
    (char*)make_request("get_total_plays"),
    expected_response
  );

  double time_end = currentTime();
  log_debug("run time: %f\n", (time_end - time_start));
}



