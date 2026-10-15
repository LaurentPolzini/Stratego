#ifndef __STRATEGO_H__
#define __STRATEGO_H__

#include "position.h"
#include "map.h"

typedef struct sBoard *tBoard;

// ---------------- CREATORS ----------------
tBoard create_board(tMap map, tArmy armyBlue, tArmy armyRed);

// ---------------- GETTERS ----------------
// Get an existing pos on map from user.
tPosition get_user_pos(void);

// Get which soldier user want to move. Has to be on his side.
tSoldier get_soldier_user(tMap map, tArmy army);

int is_soldier_moveable(tMap map, tSoldier *moveableSoldiers, int size, tSoldier soldier);

tMap get_board_map(tBoard board);

tArmy get_blue_army(tBoard board);

tArmy get_red_army(tBoard board);

enum side_color get_playing_side(tBoard board);

// returns 1 or 2 for the player to be red (first player)
int get_first_player(void);

char *get_red_name(tBoard board);

char *get_blue_name(tBoard board);

// ---------------- PLAY ----------------
// play a game until a flag is found.
void play_all_game(tBoard board);

void play_all_game_vs_robot(tBoard board);

int play_robot_turn(tBoard board);
/*
    A turn is :
        - Selecting a soldier to move
        - Selecting a square to move to.
*/
// returns if flag captured
int play_a_turn(tBoard board);

// Return 0 if did not move (lost fight), 1 if won fight.
int manage_fight_with_movement(tBoard board, tSoldier soldierThatMoves, tSoldier soldierToFight);

// ---------------- SETTERS ----------------
void set_army_on_map(tBoard board, enum side_color side);

void set_next_side(tBoard board);

// ---------------- DESTROYERS ----------------
void destroy_board(tBoard *board);


#endif