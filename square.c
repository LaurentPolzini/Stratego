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
tSquare create_square(unsigned int abciss, unsigned int ordonne) {
    tSquare square = malloc(sizeof(struct sSquare));

    square->pos = create_position(abciss, ordonne);
    square->soldier = NULL;
    square->state = EMPTY;

    return square;
}

void print_square(tSquare square) {
    if (!square) {
        printf("|??|");
        fflush(stdout);
        return;
    }
    switch (square->state)
    {
    case LAKE:
        printf("|OO|");
        break;
    case EMPTY:
        printf("|--|");
        break;
    case OCCUPIED:
        printf("|%s|", get_unit_abreviation(get_unit(square->soldier)));
        break;
    default:
        printf("|??|");
        break;
    }
    fflush(stdout);
}


// ------------------------------------ Getters ------------------------------------
int is_square_empty(tSquare square) {
    if (square) {
        return square->state == EMPTY;
    }
    return 0;
}

int is_square_lake(tSquare square) {
    if (square) {
        return square->state == LAKE;
    }
    return 0;
}

int is_square_occupied(tSquare square) {
    if (square) {
        return square->state == OCCUPIED;
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

void print_state(tSquare square) {
    if (!square) return;
    switch (square->state)
    {
    case EMPTY:
        printf("Square is Empty\n");
        break;
    case LAKE:
        printf("Square is Lake\n");
        break;
    case OCCUPIED:
        printf("Square is Occupied\n");
        break;
    default:
        break;
    }
}

// ------------------------------------ Setters ------------------------------------
void set_state(tSquare square, enum square_state stat) {
    if (square) square->state = stat;
}

int set_soldier_square(tSquare square, tSoldier soldier) {
    if (square && soldier && !is_square_lake(square)) {
        square->soldier = soldier;
        square->state = OCCUPIED;
        set_soldier_position(soldier, get_position_square(square));
        return 1;
    }

    return 0;
}

// clear a square (soldier leaves and state becomes empty)
tSoldier clear_square(tSquare square) {
    if (square) {
        //tSoldier tmp = create_soldier(get_unit(square->soldier), get_side(square->soldier), get_id(square->soldier));
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
        free(*square);
        *square = NULL;
    }
}
