
#include <criterion/criterion.h>
#include "../src/student_code.h"
#include<unistd.h>
#include "stdio.h"

#include "../src/database.h"
#include "../src/server.h"
#include "../src/common.h"

typedef struct locks_args_t {
  float delay;
  pthread_mutex_t* mutex;
} locks_args_t;

void* release_lock_after_delay(void* args) {
  // Sleep for a little bit longer than we'd expect the process to take
  fsleep(1.01*((locks_args_t*)args)->delay);
  // Release the lock
  pthread_mutex_unlock(((locks_args_t*)args)->mutex);
  // End the thread
  return NULL;
}


Test(Locks, add_player, .timeout=3*TIME_DELAY) {
  log_debug("Testing add_player locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  add_player(&db, "Sam");
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, add_player_score, .timeout=3*TIME_DELAY) {
  log_debug("Testing add_player_score locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  add_player_score(&db, "Sam", 10);
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, get_player_plays, .timeout=3*TIME_DELAY) {
  log_debug("Testing get_player_plays locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_player_plays(&db, "Sam");
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, get_player_high_score, .timeout=3*TIME_DELAY) {
  log_debug("Testing get_player_high_score locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_player_high_score(&db, "Sam");
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, get_best_player, .timeout=3*TIME_DELAY) {
  log_debug("Testing get_best_player locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_best_player(&db);
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, get_num_players, .timeout=3*TIME_DELAY) {
  log_debug("Testing get_num_players locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_num_players(&db);
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, get_highest_score, .timeout=3*TIME_DELAY) {
  log_debug("Testing get_highest_score locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_highest_score(&db);
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}

Test(Locks, get_total_plays, .timeout=3*TIME_DELAY) {
  log_debug("Testing get_total_plays locks....\n")
  // Set up variables we will need
  double start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = currentTime();

  // Lock the mutex
  pthread_mutex_lock(db.mutex);

  // Set up a background thread to unlock the mutex automatically
  locks_args_t args = {
    .delay = TIME_DELAY,
    .mutex = db.mutex
  };
  pthread_create(&unlock_thread, NULL, release_lock_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_total_plays(&db);
  end_time = currentTime();
  elapsed_time = end_time - start_time;

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= TIME_DELAY);
}



