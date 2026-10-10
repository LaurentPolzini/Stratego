#ifndef __ARMY_H__
#define __ARMY_H__

#include "soldier.h"

#define SIZE_ARMY 40

typedef struct sArmy *tArmy;

tArmy create_army(enum side_color side);

void destroy_soldier_in_army(tArmy army, tSoldier soldier);
void destroy_army(tArmy *army); // up to SIZE_ARMY soldiers

enum side_color get_army_color(tArmy army);

tSoldier get_soldier_in_army(tArmy army, int id);
tSoldier *get_soldierZ_in_army(tArmy army);

#endif