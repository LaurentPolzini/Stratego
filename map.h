#ifndef MAP_H
#define MAP_H

#include "army.h"
#include "square.h"
#include "position.h"

#define NB_LINES 10
#define NB_COLUMNS 10

typedef struct sMap *tMap;


// ------------------------------------ Creators ------------------------------------
tMap create_map(void);

// ------------------------------------ Getters ------------------------------------
tSquare **get_map(tMap map);
// Get specific square[abciss][ordonne] on map
tSquare get_square(tMap map, unsigned int abciss, unsigned int ordonne);

// Same as last function
tSquare get_square_from_pos(tMap map, tPosition pos);

// ------------------------------------ Questions ------------------------------------
// is line and column given < 10 (NB_LINES or NB_COLUMNS)
int is_position_on_map(tPosition pos);

// ------------------------------------ Setters ------------------------------------
void set_soldier_on_map(tMap map, tPosition pos, tSoldier soldier);
// clears a square and return the soldier at specific position.
tSoldier clear_square_on_map(tMap map, tPosition pos);

/*
 6 return cases :
    0 -> soldier indeed moved
    1 -> at least one of the pos is not on map
    2 -> posTo is not empty
    3 -> posFrom doesn't have a soldier
    4 -> posFrom has a soldier that can't move
    5 -> posFrom has a soldier that can not move over that distance
*/
int move_soldier_pos_to_pos(tMap map, tPosition posFrom, tPosition posTo);

int move_soldier_pos_to_square(tMap map, tPosition posFrom, tSquare squareTo);

int move_soldier_square_to_pos(tMap map, tSquare squareFrom, tPosition posTo);

int move_soldier_square_to_square(tMap map, tSquare squareFrom, tSquare squareTo);

// ------------------------------------ Destroyers ------------------------------------
void destroy_map(tMap *map);

#endif
