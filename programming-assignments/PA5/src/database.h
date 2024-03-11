
#ifndef DATABASE_H
#define DATABASE_H

//#include "student_code.h"
#include <pthread.h>

#define MAX_STRING_LENGTH 256
#define MAX_PLAYERS 64
#define MAX_CONCURRENT_READERS 4

typedef struct DatabaseEntry {
  char player_name[MAX_STRING_LENGTH];
  int num_plays;
  int high_score;
} DatabaseEntry;

typedef struct PlayerDatabase {
  DatabaseEntry* player_stats[MAX_PLAYERS];

  int readers;
  int writers;
  pthread_mutex_t* mutex;
  pthread_cond_t* can_read;
  pthread_cond_t* can_write;
} PlayerDatabase;

// Initialization function for the database
PlayerDatabase init_db();


// Setting
int do_slow_thing(float how_slow);


int _add_player(PlayerDatabase* db, char* player_name);

// set stats for a specific player
int _increment_player_plays(PlayerDatabase db, char* player_name);
int _add_player_score(PlayerDatabase db, char* player_name, int score);

// Get stats for a specific player
int _get_player_plays(PlayerDatabase db, char* player_name);
int _get_player_high_score(PlayerDatabase db, char* player_name);


// Get some statistics
char* _get_best_player(PlayerDatabase db);
int _get_num_players(PlayerDatabase db);
int _get_highest_score(PlayerDatabase db);
int _get_total_plays(PlayerDatabase db);

// Functions for the server
void pass_to_client_handler(void* arg);


#endif //DATABASE_H