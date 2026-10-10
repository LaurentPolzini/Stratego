#include <stdio.h>
#include <stdlib.h>
#include "soldier.h"
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
    soldat->pos = create_position(OUT_OF_POS, OUT_OF_POS);

    return soldat;
}


/*
    --------------------------- Destroyers ---------------------------
*/
void destroy_soldier(tSoldier *soldier) {
    if (soldier == NULL || *soldier == NULL)
        return;

    destroy_unit(&(*soldier)->unit);
    destroy_position(&(*soldier)->pos);
    free(*soldier);
    *soldier = NULL;
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
    if (!soldier) return NULL;
    return soldier->pos;
}

char *get_soldiers_name(tSoldier soldier) {
    if (!soldier) return NULL;
    return get_name(get_unit(soldier));
}

int can_soldier_move(tSoldier soldier) {
    if (!soldier) return 0;
    return can_unit_move(soldier->unit);
}

int are_soldiers_on_same_side(tSoldier soldier1, tSoldier soldier2) {
    if (soldier1 && soldier2) {
        return soldier1->side == soldier2->side;
    }
    return 0;
}

int have_soldiers_same_id(tSoldier soldier1, tSoldier soldier2) {
    if (!(soldier1 && soldier2)) return 0;
    return (soldier1->unit_id == soldier2->unit_id);
}

int is_soldier_on_pos(tSoldier soldier, tPosition pos) {
    if (!(soldier && pos)) return 0;
    return are_pos_equals(get_position(soldier), pos);
}

int can_soldier_move_this_far(tSoldier soldier, unsigned int distance) {
    if (!(soldier && distance > 0)) return 0;
    return get_movement(get_unit(soldier)) >= distance;
}

int are_soldiers_equal(tSoldier soldier1, tSoldier soldier2) {
    if (!(soldier1 && soldier2)) return 0;
    return soldier1->side == soldier2->side && soldier1->unit_id == soldier2->unit_id && are_units_equal(soldier1->unit, soldier2->unit);
}

void print_color(enum side_color color) {
    if (color == BLUE) {
        printf("Blue ");
    } else {
        printf("Red ");
    }
}

/*
    --------------------------- Setters ---------------------------
*/
void set_soldier_position(tSoldier soldier, tPosition pos) {
    if (!(soldier && pos)) return;
    set_abcisse(soldier->pos, get_abcisse(pos));
    set_ordonnee(soldier->pos, get_ordonnee(pos));
}

// Returns 1 if soldier1 won, 2 if soldier2 won, 3 if both died, 0 in other cases
// Soldiers are NOT destroyed "/!\"
int soldier_fight(tSoldier soldier1, tSoldier soldier2) {
    int soldier_winner = 0;
    if (!(soldier1 && soldier2 && !are_soldiers_on_same_side(soldier1, soldier2))) return 0;
    int which_unit_wins = who_wins(get_unit(soldier1), get_unit(soldier2));
    switch (which_unit_wins)
    {
    case 1:
        printf("%s wins the fight and kills %s\n", get_soldiers_name(soldier1), get_soldiers_name(soldier2));
        //destroy_soldier(&soldier2);
        soldier_winner = 1;
        break;
    case 2:
        printf("%s wins the fight and kills %s\n", get_soldiers_name(soldier2), get_soldiers_name(soldier1));
        //destroy_soldier(&soldier1);
        soldier_winner = 2;
        break;
    case 3:
        printf("%s and %s both died in the fight.\n", get_soldiers_name(soldier1), get_soldiers_name(soldier2));
        //destroy_soldier(&soldier1);
        //destroy_soldier(&soldier2);
        soldier_winner = 3;
        break;
    
    default:
        break;
    }

    return soldier_winner;
}
