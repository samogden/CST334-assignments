
#include <criterion/criterion.h>
#include "../src/student_code.h"
#include<unistd.h>
#include "stdio.h"

#include "../src/database.h"
#include "../src/server.h"

typedef struct conds_args_t {
  int delay;
  PlayerDatabase* db;
} conds_args_t;


/**
 * Will test a signal being sent under three conditions:
 *  1. There are too many readers
 *  2. There is a writer
 *  3. There are neither readers nor a writer
 *  Should take 3x TIME_DELAY
 * @param args
 * @return
 */
void* signal_read_after_delay(void* args) {
  PlayerDatabase* db = ((conds_args_t*)args)->db;
  int delay = ((conds_args_t*)args)->delay;

  // Check whether we are in fact respecting MAX_CONCURRENT_READERS
  sleep(delay);
  pthread_mutex_lock(db->mutex);
  db->readers = MAX_CONCURRENT_READERS;
  db->writers = 0;
  pthread_cond_signal(db->can_read);
  pthread_mutex_unlock(db->mutex);

  // Check whether we are respecting when there are writers
  sleep(delay);
  pthread_mutex_lock(db->mutex);
  db->readers = 0;
  db->writers = 1;
  pthread_cond_signal(db->can_read);
  pthread_mutex_unlock(db->mutex);

  // Finally, this should succeed
  sleep(delay);
  pthread_mutex_lock(db->mutex);
  db->readers = 0;
  db->writers = 0;
  pthread_cond_signal(db->can_read);
  pthread_mutex_unlock(db->mutex);

  return NULL;
}


/**
 * Will test a signal being sent under three conditions:
 *  1. There are any readers
 *  2. There are any writers
 *  3. There are neither readers nor a writer
 *  Should take 3x TIME_DELAY
 * @param args
 * @return
 */
void* signal_write_after_delay(void* args) {
  PlayerDatabase* db = ((conds_args_t*)args)->db;
  int delay = ((conds_args_t*)args)->delay;

  // Check whether we are in fact respecting readers
  sleep(delay);
//  log_debug("signal_write_after_delay: test readers\n")
  pthread_mutex_lock(db->mutex);
  db->readers = 1;
  db->writers = 0;
  pthread_cond_signal(db->can_write);
  pthread_mutex_unlock(db->mutex);

  // Check whether we are respecting when there are writers
  sleep(delay);
//  log_debug("signal_write_after_delay: test writers\n")
  pthread_mutex_lock(db->mutex);
  db->readers = 0;
  db->writers = 1;
  pthread_cond_signal(db->can_write);
  pthread_mutex_unlock(db->mutex);

  // Finally, this should succeed
  sleep(delay);
  pthread_mutex_lock(db->mutex);
//  log_debug("signal_write_after_delay: test good\n")
  db->readers = 0;
  db->writers = 0;
  pthread_cond_signal(db->can_write);
  pthread_mutex_unlock(db->mutex);

  return NULL;
}


Test(Conditions, add_player, .timeout=6*TIME_DELAY) {
  log_debug("Testing add_player condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_write_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  add_player(&db, "Sam");
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}

Test(Conditions, add_player_score, .timeout=6*TIME_DELAY) {
  log_debug("Testing add_player_score condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_write_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  add_player_score(&db, "Sam", 10);
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}


Test(Conditions, get_player_plays, .timeout=6*TIME_DELAY) {
  log_debug("Testing get_player_plays condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_read_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_player_plays(&db, "Sam");
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}

Test(Conditions, get_player_high_score, .timeout=6*TIME_DELAY) {
  log_debug("Testing get_player_high_score condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_read_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_player_high_score(&db, "Sam");
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}

Test(Conditions, get_best_player, .timeout=6*TIME_DELAY) {
  log_debug("Testing get_best_player condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_read_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_best_player(&db);
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}

Test(Conditions, get_num_players, .timeout=6*TIME_DELAY) {
  log_debug("Testing get_num_players condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_read_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_num_players(&db);
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}

Test(Conditions, get_highest_score, .timeout=6*TIME_DELAY) {
  log_debug("Testing get_highest_score condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_read_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_highest_score(&db);
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}

Test(Conditions, get_total_plays, .timeout=6*TIME_DELAY) {
  log_debug("Testing get_total_plays condition_variables....\n")
  // Set up variables we will need
  time_t start_time, end_time;
  double elapsed_time;
  pthread_t unlock_thread;
  PlayerDatabase db = init_db();

  // Start timer to make sure that we run for as long as we'd expect to
  start_time = time(NULL);

  // Lock the mutex
  db.readers = MAX_CONCURRENT_READERS;
  db.writers = 1;

  // Set up a background thread to unlock the mutex automatically
  conds_args_t args = {
    .delay = TIME_DELAY,
    .db = &db
  };
  pthread_create(&unlock_thread, NULL, signal_read_after_delay, (void*)&args);

  // Call the function we are testing the lock on
  get_total_plays(&db);
  end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);

  // Check to make sure that the delay time is bigger than the time delay, so we actually locked.
  // Note that we don't check an upper limit since that is enforced by out timeout.
  cr_assert(elapsed_time >= 3*TIME_DELAY);
}
