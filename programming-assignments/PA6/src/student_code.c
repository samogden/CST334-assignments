#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"
#include "server.h"
#include <stdint.h>

/*
 * This is tested by running two requests at the same time for different length of time.
 * e.g. 2-second and 3-second.  If it takes 5s then they aren't running concurrently
 *   but if it takes 3 seconds then they are.
 * Test a wide range of random times.
 */
void pass_to_client_handler(void* arg) {
  // todo: Convert this to run multi-threaded
  client_handler(arg);
}

/**
 * Using the database lock, make sure that we can safely read, and adjust variables as needed.
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void read_lock(PlayerDatabase* db) {
  // todo
  // Question: What variables do we need to check before we know we can safely read?
}

/**
 * Release the lock and adjust any variables that are necessary
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void read_unlock(PlayerDatabase* db) {
  // todo
}
/**
 * Using the database lock, make sure that we can safely write, and adjust variables as needed.
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void write_lock(PlayerDatabase* db) {
  // todo
}

/**
 * Release the lock and adjust any variables that are necessary
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void write_unlock(PlayerDatabase* db) {
  // todo
}


// Add a new player
int add_player(PlayerDatabase* db, char* player_name) {
  write_lock(db);
  int return_val = _add_player(db, player_name);
  write_unlock(db);
  return return_val;
}

// Update stats for a particular player
int add_player_score(PlayerDatabase* db, char* player_name, int score) {
  // Question: Do we realistically need to lock the entire database for this operation?
  write_lock(db);
  int return_val = _add_player_score(*db, player_name, score);
  write_unlock(db);
  return return_val;
}

// Get stats for a specific player
int get_player_plays(PlayerDatabase* db, char* player_name) {
  read_lock(db);
  int return_val = _get_player_plays(*db, player_name);
  read_unlock(db);
  return return_val;
}

int get_player_high_score(PlayerDatabase* db, char* player_name) {
  read_lock(db);
  int return_val = _get_player_high_score(*db, player_name);
  read_unlock(db);
  return return_val;
}

// Get general statistics
char* get_best_player(PlayerDatabase* db) {
  read_lock(db);
  char* return_val = _get_best_player(*db);
  read_unlock(db);
  return return_val;
}
int get_num_players(PlayerDatabase* db) {
  read_lock(db);
  int return_val = _get_num_players(*db);
  read_unlock(db);
  return return_val;
}
int get_highest_score(PlayerDatabase* db) {
  read_lock(db);
  int return_val = _get_highest_score(*db);
  read_unlock(db);
  return return_val;
}

int get_total_plays(PlayerDatabase* db) {
  read_lock(db);
  int return_val = _get_total_plays(*db);
  read_unlock(db);
  return return_val;
}


