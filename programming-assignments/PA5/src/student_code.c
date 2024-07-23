#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"
#include "server.h"
#include <stdint.h>

void pass_to_client_handler(void* arg) {
  // todo: Convert this to run multi-threaded
  client_handler(arg);
}

void read_lock(PlayerDatabase* db) {
  // todo
  // Question: What variables do we need to check before we know we can safely read?
}

void read_unlock(PlayerDatabase* db) {
  // todo
}

void write_lock(PlayerDatabase* db) {
  // todo
}

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


