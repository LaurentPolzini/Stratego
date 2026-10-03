#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "army.h"
#include "position.h"

typedef struct sSquare *tSquare;

enum square_state {EMPTY, OCCUPIED, LAKE};

// ------------------------------------ Creators ------------------------------------
tSquare create_square(unsigned int i, unsigned int j);

// ------------------------------------ Getters ------------------------------------
// Get struct_soldier of a square
tSoldier get_soldier_square(tSquare square);
// Get enum_square_state of a square
enum square_state get_state_square(tSquare square);
// Get struct_position of a square
tPosition get_position_square(tSquare square);

// is square empty
int is_square_empty(tSquare square);

// ------------------------------------ Setters ------------------------------------
// Sets a soldier on a square
void set_soldier_square(tSquare square, tSoldier soldier);
// clear a square (soldier leaves and state becomes empty)
tSoldier clear_square(tSquare square);

// ------------------------------------ Destroyers ------------------------------------
void destroy_square(tSquare *square);

#endif