#ifndef __STRATEGO_H__
#define __STRATEGO_H__

#include "position.h"
#include "map.h"

// Get an existing pos on map from user.
tPosition get_user_pos(void);

// Get which soldier user want to move. Has to be on his side.
tSoldier get_soldier_user(tMap map, enum side_color side);

/*
    A turn is :
        - Selecting a soldier to move
        - Selecting a square to move to.
*/
void play_a_turn(tMap map, tArmy armyBlue, tArmy armyRed, enum side_color who_plays);

// Return 0 if did not move (lost fight), 1 if won fight.
int manage_fight(tMap map, tArmy armyBlue, tArmy armyRed, tSoldier soldierThatMoves, tSoldier soldierToFight);

#endif