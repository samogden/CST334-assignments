#ifndef __student_code_h__
#define __student_code_h__

#include <pthread.h>
#include "database.h"


/*
 * This is tested by running two requests at the same time for different length of time.
 * e.g. 2-second and 3-second.  If it takes 5s then they aren't running concurrently
 *   but if it takes 3 seconds then they are.
 * Test a wide range of random times.
 */
void pass_to_client_handler(void* arg);


/**
 * Using the database lock, make sure that we can safely read, and adjust variables as needed.
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void read_lock(PlayerDatabase* db);


/**
 * Release the lock and adjust any variables that are necessary
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void read_unlock(PlayerDatabase* db);


/**
 * Using the database lock, make sure that we can safely write, and adjust variables as needed.
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void write_lock(PlayerDatabase* db);


/**
 * Release the lock and adjust any variables that are necessary
 * Note that this requires checking the number of current readers and writers, and using the appropriate condition variable.
 * @param db
 */
void write_unlock(PlayerDatabase* db);


DatabaseEntry* get_player(PlayerDatabase, char* player_name);

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




#endif
