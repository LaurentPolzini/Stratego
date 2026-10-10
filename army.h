#ifndef __ARMY_H__
#define __ARMY_H__

#include "soldier.h"

#define SIZE_ARMY 40

typedef struct sArmy *tArmy;

// ---- CREATORS ----
tArmy create_army(enum side_color side);

// ---- DESTROYERS ----
void destroy_soldier_in_army(tArmy army, tSoldier soldier);
void destroy_army(tArmy *army); // up to SIZE_ARMY soldiers

// ---- GETTERS----
tSoldier get_soldier_in_army(tArmy army, int id);
tSoldier *get_soldierZ_in_army(tArmy army);
int is_soldier_on_army_side(tArmy army, tSoldier soldier);
enum side_color get_army_color(tArmy army);

#endif