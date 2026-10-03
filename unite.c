#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unite.h"

struct sUnite {
    char *name;
    unsigned int strengh;
    unsigned int movement;
};

/*    Creators    */
tUnite create_spy(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    unit->name = "spy";
    unit->strengh = 1;
    unit->movement = 1;

    return unit;
}

tUnite create_scout(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "scout";
    unit->strengh = 2;
    unit->movement = 10;

    return unit;
}

tUnite create_miner(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "miner";
    unit->strengh = 3;
    unit->movement = 1;

    return unit;
}

tUnite create_sergeant(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "sergeant";
    unit->strengh = 4;
    unit->movement = 1;

    return unit;
}

tUnite create_lieutenant(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "lieutenant";
    unit->strengh = 5;
    unit->movement = 1;

    return unit;
}

tUnite create_captain(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "captain";
    unit->strengh = 6;
    unit->movement = 1;

    return unit;
}

tUnite create_major(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "major";
    unit->strengh = 7;
    unit->movement = 1;

    return unit;
}

tUnite create_colonel(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "colonel";
    unit->strengh = 8;
    unit->movement = 1;

    return unit;
}

tUnite create_general(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "general";
    unit->strengh = 9;
    unit->movement = 1;

    return unit;
}

tUnite create_marshall(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "marshall";
    unit->strengh = 10;
    unit->movement = 1;

    return unit;
}

tUnite create_bomb(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "bomb";
    unit->strengh = 100;
    unit->movement = 0;

    return unit;
}

tUnite create_flag(void) {
    tUnite unit = malloc(sizeof(struct sUnite));
    if (!unit) return NULL;
    unit->name = "flag";
    unit->strengh = 0;
    unit->movement = 0;

    return unit;
}

/*     Destroy     */
void destroy_unit(tUnite *unit) {
    if (unit && *unit) {
        free(*unit);
        *unit = NULL;
    }
}

/*    Getters   */
char *get_name(tUnite unit) {
    if (unit) {
        return unit->name;
    }
    return NULL;
}

unsigned int get_strengh(tUnite unit) {
    if (unit) {
        return unit->strengh;
    }
    return -1;
}

unsigned int get_movement(tUnite unit) {
    if (unit) {
        return unit->movement;
    }
    return -1;
}

int is_spy(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 1) && !(strcmp(unit->name, "spy"));
}

int is_scout(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 2) && !(strcmp(unit->name, "scout"));
}

int is_miner(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 3) && !(strcmp(unit->name, "miner"));
}

int is_sergeant(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 4) && !(strcmp(unit->name, "sergeant"));
}

int is_lieutenant(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 5) && !(strcmp(unit->name, "lieutenant"));
}

int is_captain(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 6) && !(strcmp(unit->name, "captain"));
}

int is_major(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 7) && !(strcmp(unit->name, "major"));
}

int is_colonel(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 8) && !(strcmp(unit->name, "colonel"));
}

int is_general(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 9) && !(strcmp(unit->name, "general"));
}

int is_marshall(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 10) && !(strcmp(unit->name, "marshall"));
}

int is_bomb(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 100) && !(strcmp(unit->name, "bomb"));
}

int is_flag(tUnite unit) {
    if (!unit) return 0;
    return (unit->strengh == 0) && !(strcmp(unit->name, "flag"));
}


/*    Fight    */
// (internal functions)
int bomb_effect(tUnite unit1, tUnite unit2); // special rule if a unit is a bomb
int spy_fights(tUnite unit1, tUnite unit2); // special rule if spy fights
int actual_fight(tUnite unit1, tUnite unit2); // strengh comparison

// returns 1, 2 or 3 (being unit 1 and unit2 in order. 3 if both units are killed)
int who_wins(tUnite unit1, tUnite unit2) {
    if (!(unit1 && unit2)) return 0;
    int winner = 0;
    if (is_flag(unit1) || is_flag(unit2)) { // flag
        winner = is_flag(unit1) ? 2 : 1; // one of them is flag. If not unit1, unit2.
    } else {
        if (is_bomb(unit1) || is_bomb(unit2)) { // on of the units is a bomb
            winner = bomb_effect(unit1, unit2);
        } else { // not a bomb
            if (is_spy(unit1) || is_spy(unit2)) { // spy fights
                winner = spy_fights(unit1, unit2);
            } else { // no special case. Casual fight. (Not a flag, not a bomb)
                winner = actual_fight(unit1, unit2);
            }
        }
    }
    return winner;
}
// compares strengh
int actual_fight(tUnite unit1, tUnite unit2) {
    if (!(unit1 && unit2)) return 0;
    int winner = 0;
    if (unit1->strengh > unit2->strengh) { // unit1 strengh higher than unit2 strengh
        winner = 1;
    } else {
        if (unit1->strengh < unit2->strengh) { // unit2 strengh higher than unit1 strengh
            winner = 2;
        } else { // same unit
            winner = 3;
        }
    }
    return winner;
}

/*    Special Rules    */
// If at least one of the units is a spy, a special rule applies if marshall
int spy_fights(tUnite unit1, tUnite unit2) {
    if (!(unit1 && unit2)) return 0;
    int winner = 0;

    int isSpy1 = is_spy(unit1);
    int isSpy2 = is_spy(unit2);
    
    if (!(isSpy1 || isSpy2)) { // not spies !
        return 0;
    }
    if (isSpy1 && is_marshall(unit2)) {
        winner = 1;
    } else {
        if (isSpy2 && is_marshall(unit1)) {
            winner = 2;
        } else {
            winner = actual_fight(unit1, unit2);
        }
    }
    return winner;
}

// If one of the fighting units is a bomb, who wins (other unit might be miner)
int bomb_effect(tUnite unit1, tUnite unit2) {
    if (!(unit1 && unit2)) return 0;
    int winner = 0;

    int isbombu1 = is_bomb(unit1);
    
    if (!(isbombu1 || is_bomb(unit2))) { // not a bomb !
        return 0;
    }
    if (isbombu1) {
        if (is_miner(unit2)) { // unit2 is miner
            winner = 2;
        } else {
            winner = 1; // unit2 is anything but miner
        }
    } else { // unit 2 is bomb
        if (is_miner(unit1)) { // unit1 is miner
            winner = 1;
        } else {
            winner = 2; // unit2 is anything but miner
        }
    }
    return winner;
}

