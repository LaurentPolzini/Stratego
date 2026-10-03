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

#define SIZE_ARMY 40

enum side_color {BLUE, RED};

typedef struct sSoldier *tSoldier;

/*
    --------------------------- Soldier & Army creation ---------------------------
*/
// soldier needs unit's @.
tSoldier create_soldier(tUnite unit, enum side_color side, int id); // a retirer. Juste pour les tests
tSoldier *create_army(enum side_color side);

// Destroyers
void destroy_unit_in_army(tSoldier *army, int id);
void destroy_soldier(tSoldier *soldier);
void destroy_army(tSoldier **army); // up to SIZE_ARMY soldiers

/*
    --------------------------- Getters ---------------------------
*/
int get_id(tSoldier soldier);

enum side_color get_side(tSoldier soldier);

tUnite get_unit(tSoldier soldier);

tPosition get_position(tSoldier soldier);

/*
    --------------------------- Setters ---------------------------
*/
void set_position(tSoldier soldier, tPosition pos);

#endif