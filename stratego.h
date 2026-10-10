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

tSoldier *which_soldiers_can_move(tMap map, tArmy army, int *how_many_can_move);

tMap get_board_map(tBoard board);

tArmy get_blue_army(tBoard board);

tArmy get_red_army(tBoard board);

enum side_color get_playing_side(tBoard board);

// ---------------- PLAY ----------------
/*
    A turn is :
        - Selecting a soldier to move
        - Selecting a square to move to.
*/
void play_a_turn(tBoard board);

// Return 0 if did not move (lost fight), 1 if won fight.
int manage_fight_with_movement(tBoard board, tSoldier soldierThatMoves, tSoldier soldierToFight);

// ---------------- DESTROYERS ----------------
void destroy_board(tBoard *board);


#endif