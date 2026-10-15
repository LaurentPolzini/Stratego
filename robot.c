#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "robot.h"
#include "map.h"
#include "army.h"
#include "position.h"
#include "square.h"
#include "soldier.h"

int rand_number_below_x(int x) {
    srand(time(NULL));
    if (x >= 0) {
        return rand() % (x + 1);
    }
    return OUT_OF_POS;
}

void shuffle_array(tSoldier *soldiers, int size) {
    if (!(soldiers && size > 0)) return;
    tSoldier soldTmp;
    int rand_place_to_go = OUT_OF_POS;
    for (int i = 0 ; i < size ; ++i) {
        rand_place_to_go = rand() % size;
        soldTmp = soldiers[i];
        soldiers[i] = soldiers[rand_place_to_go];
        soldiers[rand_place_to_go] = soldTmp;
    }
}

void set_army_randomly(tMap map, tArmy army) {
    if (!(map && army)) return;
    srand(time(NULL));
    tPosition *available_pos = malloc(sizeof(tPosition) * SIZE_ARMY);
    int *are_available = malloc(sizeof(int) * SIZE_ARMY);

    tSoldier *tmp = get_soldierZ_in_army(army);
    tSoldier *soldierz = copy_soldiers(tmp, SIZE_ARMY);
    shuffle_array(soldierz, SIZE_ARMY);

    int base_abcisse = 0;
    base_abcisse += (get_side(tmp[0]) == RED ? 6 : 0);

    for (int i = 0 ; i < 4 ; ++i) {
        for (int j = 0 ; j < NB_COLUMNS ; ++j) {
            available_pos[(i * NB_COLUMNS) + j] = create_position(base_abcisse + i, j);
            are_available[(i * NB_COLUMNS) + j] = 1;
        }
    }
    int rand_ind = SIZE_ARMY + 1;

    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        do {
            rand_ind = rand() % SIZE_ARMY;
        } while (!are_available[rand_ind]);
        are_available[rand_ind] = 0;
        set_soldier_on_map(map, available_pos[rand_ind], tmp[get_id(soldierz[rand_ind])]);
    }
    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        destroy_position(&(available_pos[i]));
        destroy_soldier(&(soldierz[i]));
    }
    free(available_pos);
    free(soldierz);
    free(are_available);
}

// Moves a random soldier
void random_soldier_to_square(tMap map, tArmy army, tSoldier *soldierToMove, tSquare *squareToMoveTo) {
    if (!(map && army && soldierToMove && squareToMoveTo)) return;

    // who can move ?
    int sizeArraySoldierz = 0;
    tSoldier *moveables = which_soldiers_can_move(map, army, &sizeArraySoldierz);
    if (sizeArraySoldierz == 0) {
        *soldierToMove = NULL;
        *squareToMoveTo = NULL;
        return;
    }
    // pick one
    int indRandSoldier = rand_number_below_x(sizeArraySoldierz - 1);
    tSoldier pickedSoldier = (get_soldierZ_in_army(army))[get_id(moveables[indRandSoldier])];

    // pick a square he can move to
    int sizeArraySquare = 0;
    tSquare *squaresMoveable = get_squares_he_can_move_to(map, pickedSoldier, &sizeArraySquare);
    int indRandSquare = rand_number_below_x(sizeArraySquare - 1);

    //move him
    //move_soldier_to_pos(map, pickedSoldier, get_position_square(squaresMoveable[indRandSquare]));
    *soldierToMove = pickedSoldier;
    *squareToMoveTo = squaresMoveable[indRandSquare];

    free(moveables);
    free(squaresMoveable);
}
