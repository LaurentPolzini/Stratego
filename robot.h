#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "map.h"
#include "army.h"

void set_army_randomly(tMap map, tArmy army);

void random_soldier_to_square(tMap map, tArmy army, tSoldier *soldierToMove, tSquare *squareToMoveTo);

#endif
