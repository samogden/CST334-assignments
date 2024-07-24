
#ifndef DATABASE_H
#define DATABASE_H

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

/**
 * Passes a client off to a client handler.
 * Note: your task is to modify this function to make the server non-blocking (i.e. multi-threaded)
 * Note: proper implementation of this may cause a few tests that initially were passing to fail.
 *      This is expected and you'll be fixing them with locks and condition variables.
 * Hint:  This is tested by running two requests at the same time for different length of time.
 *      e.g. 2-second and 3-second.  If it takes 5s then they aren't running concurrently
 *          but if it takes 3 seconds then they are.
 * @param: arg (void*): arguments being pased through to client handler
 */
void pass_to_client_handler(void* arg);

/**
 * Using the database lock, make sure that we start a reading state by checking and updating state variables.
 * @param db (PlayerDatabase*): the database object
 */
void read_lock(PlayerDatabase* db);


/**
 * Using the database lock, make sure that we end a reading state by checking and updating state variables.
 * @param db (PlayerDatabase*): the database object
 */
void read_unlock(PlayerDatabase* db);


/**
 * Using the database lock, make sure that we start a writing state by checking and updating state variables.
 * @param db (PlayerDatabase*): the database object
 */
void write_lock(PlayerDatabase* db);


/**
 * Using the database lock, make sure that we end a writing state by checking and updating state variables.
 * @param db (PlayerDatabase*): the database object
 */
void write_unlock(PlayerDatabase* db);



// Initialization function for the database
PlayerDatabase init_db();

// Setting
int do_slow_thing(float how_slow);

// Functions for the server
void pass_to_client_handler(void* arg);

// Add a new player
int add_player(PlayerDatabase* db, char* player_name);

// set stats for a specific player
int add_player_score(PlayerDatabase* db, char* player_name, int score);

// Get stats for a specific player
int get_player_plays(PlayerDatabase* db, char* player_name);
int get_player_high_score(PlayerDatabase* db, char* player_name);


// Get some statistics
char* get_best_player(PlayerDatabase* db);
int get_num_players(PlayerDatabase* db);
int get_highest_score(PlayerDatabase* db);
int get_total_plays(PlayerDatabase* db);

DatabaseEntry* get_player(PlayerDatabase, char* player_name);




#endif //DATABASE_H