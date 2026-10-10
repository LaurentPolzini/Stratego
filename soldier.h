#ifndef ARMY_H
#define ARMY_H

#include "unite.h"
#include "position.h"

#define NB_FLAG 1
#define NB_SPY 1
#define NB_BOMB 6
#define NB_MARSHALL 1
#define NB_GENERAL 1
#define NB_COLONEL 2
#define NB_MAJOR 3
#define NB_CAPTAIN 4
#define NB_LIEUTENANT 4
#define NB_SERGEANT 4
#define NB_MINER 5
#define NB_SCOUT 8

enum side_color {BLUE, RED};

typedef struct sSoldier *tSoldier;

/*
    --------------------------- Soldier creation ---------------------------
*/
// soldier needs unit's @.
tSoldier create_soldier(tUnite unit, enum side_color side, int id); // a retirer. Juste pour les tests

// Destroyers
void destroy_soldier(tSoldier *soldier);

tSoldier create_general_soldier(enum side_color side, int id);
tSoldier create_colonel_soldier(enum side_color side, int id);
tSoldier create_major_soldier(enum side_color side, int id);
tSoldier create_captain_soldier(enum side_color side, int id);
tSoldier create_lieutenant_soldier(enum side_color side, int id);
tSoldier create_sergeant_soldier(enum side_color side, int id);
tSoldier create_miner_soldier(enum side_color side, int id);
tSoldier create_scout_soldier(enum side_color side, int id);
tSoldier create_bomb_soldier(enum side_color side, int id);
tSoldier create_marshall_soldier(enum side_color side, int id);
tSoldier create_spy_soldier(enum side_color side, int id);
tSoldier create_flag_soldier(enum side_color side, int id);

/*
    --------------------------- Getters ---------------------------
*/
int get_id(tSoldier soldier);

enum side_color get_side(tSoldier soldier);

tUnite get_unit(tSoldier soldier);

tPosition get_position(tSoldier soldier);

char *get_soldiers_name(tSoldier soldier);

int can_soldier_move(tSoldier soldier);

// Are soldiers on the same side
int are_soldiers_on_same_side(tSoldier soldier1, tSoldier soldier2);

int have_soldiers_same_id(tSoldier soldier1, tSoldier soldier2);

// soldier.pos == pos
int is_soldier_on_pos(tSoldier soldier, tPosition pos);

int can_soldier_move_this_far(tSoldier soldier, unsigned int distance);

int are_soldiers_equal(tSoldier soldier1, tSoldier soldier2);

void print_color(enum side_color color);

/*
    --------------------------- Setters ---------------------------
*/
void set_soldier_position(tSoldier soldier, tPosition pos);

// Returns 1 if soldier1 won, 2 if soldier2 won, 3 if both died, 0 in other cases
// Soldiers are NOT destroyed "/!\"
int soldier_fight(tSoldier soldier1, tSoldier soldier2);

#endif