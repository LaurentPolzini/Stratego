#include <stdio.h>
#include <stdlib.h>
#include "army.h"
#include "soldier.h"
#include "unite.h"
#include "position.h"

struct sArmy {
    tSoldier *soldiers;
    enum side_color side;
};

/*
    --------------------------- Creators ---------------------------
*/
tArmy create_army(enum side_color side) {
    tArmy army = malloc(sizeof(struct sArmy));
    army->side = side;
    army->soldiers = malloc(sizeof(tSoldier) * SIZE_ARMY);
    int index = 0; // keep track of array

    // solo units
    army->soldiers[index] = create_general_soldier(side, index);
    ++index;
    army->soldiers[index] = create_marshall_soldier(side, index);
    ++index;
    army->soldiers[index] = create_spy_soldier(side, index);
    ++index;
    army->soldiers[index] = create_flag_soldier(side, index);
    ++index;

    for (int i = 0 ; i < NB_COLONEL ; ++i) {
        army->soldiers[index] = create_colonel_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_MAJOR ; ++i) {
        army->soldiers[index] = create_major_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_CAPTAIN ; ++i) {
        army->soldiers[index] = create_captain_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_LIEUTENANT ; ++i) {
        army->soldiers[index] = create_lieutenant_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_SERGEANT ; ++i) {
        army->soldiers[index] = create_sergeant_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_MINER ; ++i) {
        army->soldiers[index] = create_miner_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_SCOUT ; ++i) {
        army->soldiers[index] = create_scout_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_BOMB ; ++i) {
        army->soldiers[index] = create_bomb_soldier(side, index);
        ++index;
    }

    return army;
}


/*
    --------------------------- Destroyers ---------------------------
*/
void destroy_army(tArmy *army) {
    if (!(*army)) return;
    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        destroy_soldier(&(((*army)->soldiers)[i]));
    }
    free((*army)->soldiers);
    (*army)->soldiers = NULL;
    free(*army);
    *army = NULL;
}
void destroy_soldier_in_army(tArmy army, tSoldier soldier) {
    if (army && soldier) {
        int id = get_id(soldier);
        if (army->soldiers[id]) {
            destroy_soldier(&(army->soldiers[id]));
            army->soldiers[id] = NULL;
        }
    }
}

/*
    --------------------------- Getters ---------------------------
*/
tSoldier get_soldier_in_army(tArmy army, int id) {
    if (army && (id > 0 && id < (SIZE_ARMY - 1))) {
        return army->soldiers[id];
    }
    return NULL;
}

enum side_color get_army_color(tArmy army) {
    if (army) {
        return army->side;
    }
    return BLUE;
}

tSoldier *get_soldierZ_in_army(tArmy army) {
    if (!army) return NULL;
    return army->soldiers;
}
