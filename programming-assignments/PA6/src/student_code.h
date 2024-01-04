#ifndef __student_code_h__
#define __student_code_h__

#include <pthread.h>
#include "database.h"


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

// Functions for the server
void pass_to_client_handler(void* arg);




#endif
