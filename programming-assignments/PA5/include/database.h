
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

/**
 * Initialize the database.  Must be called prior to using database
 * @return
 */
PlayerDatabase init_db();

/**
 * Add in a delay to the database in order to force threading to be important
 * @param how_slow : delay in seconds
 * @return
 */
int do_slow_thing(float how_slow);

/**
 * Adds a player to the database, with some delay
 * @param db
 * @param player_name
 * @return
 */
int add_player(PlayerDatabase* db, char* player_name);

/**
 * Adds a player score to the database, with some delay
 * @param db
 * @param player_name
 * @param score
 * @return
 */
int add_player_score(PlayerDatabase* db, char* player_name, int score);

/**
 * Gets the score of a particular player, with some delay
 * @param db
 * @param player_name
 * @return
 */
int get_player_plays(PlayerDatabase* db, char* player_name);

/**
 * Gets the highest score of a given player, with some delay
 * @param db
 * @param player_name
 * @return
 */
int get_player_high_score(PlayerDatabase* db, char* player_name);

/**
 * Finds the player with the highest score across the entire database
 * @param db
 * @return
 */
char* get_best_player(PlayerDatabase* db);

/**
 * finds how many players are registered in the database
 * @param db
 * @return
 */
int get_num_players(PlayerDatabase* db);

/*
 * Finds the highest score for any player in the database
 */
int get_highest_score(PlayerDatabase* db);

/**
 * finds how many games have been played across the entire database
 * @param db
 * @return
 */
int get_total_plays(PlayerDatabase* db);

/**
 * Returns the entry associated with a particular player name in the database
 * @param player_name
 * @return
 */
DatabaseEntry* get_player(PlayerDatabase, char* player_name);

#endif //DATABASE_H