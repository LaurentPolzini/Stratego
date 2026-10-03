#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "army.h"
#include "position.h"

struct sSquare {
    tSoldier soldier;
    enum square_state state;
    tPosition pos;
};

// ------------------------------------ Creators ------------------------------------
tSquare create_square(unsigned int i, unsigned int j) {
    tSquare square = malloc(sizeof(struct sSquare));

    square->pos = create_position(i, j);
    square->soldier = NULL;
    square->state = EMPTY;

    return square;
}

// ------------------------------------ Getters ------------------------------------
int is_square_empty(tSquare square) {
    if (square) {
        return square->state == EMPTY;
    }
    return 0;
}

// For struct SQUARE
tSoldier get_soldier_square(tSquare square) {
    if (square) {
        return square->soldier;
    }
    return NULL;
}

enum square_state get_state_square(tSquare square) {
    if (square) {
        return square->state;
    }
    return LAKE;
}

tPosition get_position_square(tSquare square) {
    if (square) {
        return square->pos;
    }
    return NULL;
}

// ------------------------------------ Setters ------------------------------------
void set_soldier_square(tSquare square, tSoldier soldier) {
    if (square && soldier && is_square_empty(square)) {
        square->soldier = soldier;
        square->state = OCCUPIED;
    }
}
// clear a square (soldier leaves and state becomes empty)
tSoldier clear_square(tSquare square) {
    if (square) {
        tSoldier tmp = square->soldier;
        square->soldier = NULL;
        square->state = EMPTY;
        return tmp;
    }
    return NULL;
}

// ------------------------------------ Destroyers ------------------------------------
void destroy_square(tSquare *square) {
    if (square && *square) {
        destroy_position(&((*square)->pos));
        destroy_soldier(&((*square)->soldier));
        free(*square);
        *square = NULL;
    }
}
