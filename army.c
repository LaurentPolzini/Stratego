#include <stdio.h>
#include <stdlib.h>
#include "army.h"
#include "unite.h"
#include "position.h"

struct sSoldier {
    enum side_color side;
    int unit_id; // unique ID for each unit. Can find one specific unit faster (id is index in array)
    tUnite unit;
    tPosition pos;
};

/*
    --------------------------- Creators ---------------------------
*/
tSoldier create_general_soldier(enum side_color side, int id) {
    return create_soldier(create_general(), side, id);
}

tSoldier create_colonel_soldier(enum side_color side, int id) {
    return create_soldier(create_colonel(), side, id);
}

tSoldier create_major_soldier(enum side_color side, int id) {
    return create_soldier(create_major(), side, id);
}

tSoldier create_captain_soldier(enum side_color side, int id) {
    return create_soldier(create_captain(), side, id);
}

tSoldier create_lieutenant_soldier(enum side_color side, int id) {
    return create_soldier(create_lieutenant(), side, id);
}

tSoldier create_sergeant_soldier(enum side_color side, int id) {
    return create_soldier(create_sergeant(), side, id);
}

tSoldier create_miner_soldier(enum side_color side, int id) {
    return create_soldier(create_miner(), side, id);
}

tSoldier create_scout_soldier(enum side_color side, int id) {
    return create_soldier(create_scout(), side, id);
}

tSoldier create_bomb_soldier(enum side_color side, int id) {
    return create_soldier(create_bomb(), side, id);
}

tSoldier create_marshall_soldier(enum side_color side, int id) {
    return create_soldier(create_marshall(), side, id);
}

tSoldier create_spy_soldier(enum side_color side, int id) {
    return create_soldier(create_spy(), side, id);
}

tSoldier create_flag_soldier(enum side_color side, int id) {
    return create_soldier(create_flag(), side, id);
}

tSoldier create_soldier(tUnite unit, enum side_color side, int id) {
    tSoldier soldat = malloc(sizeof(struct sSoldier));
    if (!soldat) {
        return NULL;
    }
    soldat->side = side;
    soldat->unit = unit;
    soldat->unit_id = id;
    soldat->pos = create_position(50, 50);

    return soldat;
}

tSoldier *create_army(enum side_color side) {
    tSoldier *army = malloc(sizeof(struct sSoldier) * SIZE_ARMY);
    int index = 0; // keep track of array

    // solo units
    army[index] = create_general_soldier(side, index);
    ++index;
    army[index] = create_marshall_soldier(side, index);
    ++index;
    army[index] = create_spy_soldier(side, index);
    ++index;
    army[index] = create_flag_soldier(side, index);
    ++index;

    for (int i = 0 ; i < NB_COLONEL ; ++i) {
        army[index] = create_colonel_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_MAJOR ; ++i) {
        army[index] = create_major_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_CAPTAIN ; ++i) {
        army[index] = create_captain_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_LIEUTENANT ; ++i) {
        army[index] = create_lieutenant_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_SERGEANT ; ++i) {
        army[index] = create_sergeant_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_MINER ; ++i) {
        army[index] = create_miner_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_SCOUT ; ++i) {
        army[index] = create_scout_soldier(side, index);
        ++index;
    }

    for (int i = 0 ; i < NB_BOMB ; ++i) {
        army[index] = create_bomb_soldier(side, index);
        ++index;
    }

    return army;
}

/*
    --------------------------- Destroyers ---------------------------
*/
void destroy_unit_in_army(tSoldier *army, int id) {
    if (army) {
        if (army[id]) {
            destroy_soldier(&(army[id]));
            army[id] = NULL;
        }
    }
}

void destroy_soldier(tSoldier *soldier) {
    if (soldier && *soldier) {
        destroy_position(&((*soldier)->pos));
        destroy_unit(&((*soldier)->unit));
        free(*soldier);
        *soldier = NULL;
    }
}

void destroy_army(tSoldier **army) {
    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        destroy_soldier(&((*army)[i]));
    }
    free(*army);
    *army = NULL;
}

/*
    --------------------------- Getters ---------------------------
*/
tUnite get_unit(tSoldier soldier) {
    if (soldier) {
        return soldier->unit;
    }
    return NULL;
}

enum side_color get_side(tSoldier soldier) {
    if (soldier) {
        return soldier->side;
    }
    return BLUE; // not fund of this
}

int get_id(tSoldier soldier) {
    if (soldier) {
        return soldier->unit_id;
    }
    return -1;
}

tPosition get_position(tSoldier soldier) {
    return soldier->pos;
}


/*
    --------------------------- Setters ---------------------------
*/
void set_position(tSoldier soldier, tPosition pos) {
    soldier->pos = pos;
}
