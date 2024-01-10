
#include "database.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

// Initialization function for the database
PlayerDatabase init_db() {
  PlayerDatabase db = {
    .mutex = malloc(sizeof(pthread_mutex_t)),
    .can_read = malloc(sizeof(pthread_cond_t)),
    .can_write = malloc(sizeof(pthread_cond_t)),
    .readers = 0,
    .writers = 0
  };
  for (int i = 0; i < MAX_PLAYERS; i++) {
    db.player_stats[i] = NULL;
  }
  pthread_mutex_init(db.mutex, NULL);
  pthread_cond_init(db.can_read, NULL);
  pthread_cond_init(db.can_write, NULL);

  return db;
}

DatabaseEntry* get_player(PlayerDatabase db, char* player_name) {
  int curr_idx = 0;
  while (db.player_stats[curr_idx] != NULL && curr_idx < MAX_PLAYERS) {
    if (strcmp(player_name, db.player_stats[curr_idx]->player_name) == 0) {
      return db.player_stats[curr_idx];
    }
    curr_idx++;
  }
  return NULL;
}

int do_slow_thing(float how_slow) {
  // Question: What am I using this function for?  Which unit test is it most associated with?
  fsleep(how_slow);
  return how_slow;
}


// Add a new player
int _add_player(PlayerDatabase* db, char* player_name) {
  do_slow_thing(TIME_DELAY);
  int curr_idx = 0;
  int inserted_idx = -1;
  while (curr_idx < MAX_PLAYERS) {
    if (db->player_stats[curr_idx] == NULL) {
      db->player_stats[curr_idx] = malloc(sizeof(DatabaseEntry));
      strcpy(db->player_stats[curr_idx]->player_name, player_name);
      db->player_stats[curr_idx]->high_score = 0;
      db->player_stats[curr_idx]->num_plays = 0;
      inserted_idx = curr_idx;
      break;
    } else {
      if (strcmp(db->player_stats[curr_idx]->player_name, player_name) == 0) { return -1; };
    }
    curr_idx++;
  }
  return inserted_idx;
}

// Update stats for a particular player
int _add_player_score(PlayerDatabase db, char* player_name, int score) {
  do_slow_thing(TIME_DELAY);
  DatabaseEntry* player = get_player(db, player_name);
  if (player == NULL) { return -1; }
  if (player->high_score < score) {
    player->high_score = score;
  }
  player->num_plays++;
  return player->high_score;
}

// Get stats for a specific player
int _get_player_plays(PlayerDatabase db, char* player_name) {
  do_slow_thing(TIME_DELAY);
  DatabaseEntry* player = get_player(db, player_name);
  if (player == NULL) { return -1; }
  return player->num_plays;
}
int _get_player_high_score(PlayerDatabase db, char* player_name) {
  do_slow_thing(TIME_DELAY);
  DatabaseEntry* player = get_player(db, player_name);
  if (player == NULL) { return -1; }
  return player->high_score;
}

// Get general statistics
char* _get_best_player(PlayerDatabase db) {
  do_slow_thing(TIME_DELAY);
  // Check to make sure we have players
  if (db.player_stats[0] == NULL) {
    return NULL;
  }

  int best_player_idx = 0;
  int curr_idx = 1; // Since we assume the best is index 0 to begin with, this should be safe
  while (db.player_stats[curr_idx] != NULL && curr_idx < MAX_PLAYERS) {
    if (db.player_stats[curr_idx]->high_score > db.player_stats[best_player_idx]->high_score) {
      best_player_idx = curr_idx;
    }
    curr_idx++;
  }
  return db.player_stats[best_player_idx]->player_name;
}

int _get_num_players(PlayerDatabase db) {
  do_slow_thing(TIME_DELAY);
  int curr_idx = 0;
  while (db.player_stats[curr_idx] != NULL && curr_idx < MAX_PLAYERS) {
    curr_idx++;
  }
  return curr_idx;
}
int _get_highest_score(PlayerDatabase db) {
  do_slow_thing(TIME_DELAY);
  // Check to make sure we have players
  if (db.player_stats[0] == NULL) {
    return 0;
  }

  int best_player_idx = 0;
  int curr_idx = 1; // Since we assume the best is index 0 to begin with, this should be safe
  while (db.player_stats[curr_idx] != NULL && curr_idx < MAX_PLAYERS) {
    if (db.player_stats[curr_idx]->high_score > db.player_stats[best_player_idx]->high_score) {
      best_player_idx = curr_idx;
    }
    curr_idx++;
  }
  return db.player_stats[best_player_idx]->high_score;
}

int _get_total_plays(PlayerDatabase db) {
  do_slow_thing(TIME_DELAY);
  int total_score = 0;
  int curr_idx = 0;
  while (db.player_stats[curr_idx] != NULL && curr_idx < MAX_PLAYERS) {
    total_score += db.player_stats[curr_idx]->num_plays;
    curr_idx++;
  }
  return total_score;
}

