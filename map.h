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
// Get specific square[i][j] on map. i being lines and j columns
tSquare get_square(tMap map, unsigned int i, unsigned int j);

// ------------------------------------ Questions ------------------------------------
// is line and column given < 10 (NB_LINES or NB_COLUMNS)
int is_position_on_map(tPosition pos);

// ------------------------------------ Destroyers ------------------------------------
void destroy_map(tMap *map);

// ------------------------------------ Setters ------------------------------------
void set_soldier_on_map(tMap map, tPosition pos, tSoldier soldier);
// clears a square and return the soldier at specific position.
tSoldier clear_square_on_map(tMap map, tPosition pos);

#endif
