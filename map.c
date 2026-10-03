#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "army.h"
#include "square.h"
#include "position.h"

struct sMap {
    tSquare **squares; // NB_LINES * NB_COLUMNS
};

// ------------------------------------ Creators ------------------------------------
tMap create_map(void) {
    tMap map = malloc(sizeof(struct sMap));
    if (!map) return NULL;

    map->squares = malloc(sizeof(tSquare *) * NB_LINES);
    if (!map->squares) {
        free(map);
        return NULL;
    }

    for (unsigned int i = 0 ; i < NB_LINES ; ++i) {
        map->squares[i] = malloc(sizeof(tSquare) * NB_COLUMNS);
        if (!map->squares[i]) {
            // free allocated ressources
            for (unsigned int k = 0; k < i; ++k)
                free(map->squares[k]);

            free(map->squares);
            free(map);
            return NULL;
        }
        for (unsigned int j = 0 ; j < NB_COLUMNS ; ++j) {
            (map->squares)[i][j] = create_square(i, j);

        }
    }

    return map;
}

// ------------------------------------ Getters ------------------------------------
// For struct MAP
tSquare **get_map(tMap map) {
    if (map) {
        return map->squares;
    }
    return NULL;
}

tSquare get_square(tMap map, unsigned int abciss, unsigned int ordonne) {
    if (map && (abciss < NB_LINES) && (ordonne < NB_COLUMNS)) {
        return (map->squares)[abciss][ordonne];
    }
    return NULL;
}

tSquare get_square_from_pos(tMap map, tPosition pos) {
    if (map && pos && 
        (get_abcisse(pos) < NB_LINES) && (get_ordonnee(pos) < NB_COLUMNS)) {
        return (map->squares)[get_abcisse(pos)][get_ordonnee(pos)];
    }
    return NULL;
}

// return if line and column given by pos is < 40.
int is_position_on_map(tPosition pos) {
    if (pos) {
        return (get_abcisse(pos) < NB_LINES)
            && (get_ordonnee(pos) < NB_COLUMNS);
    }
    return 0;
}

// ------------------------------------ Setters ------------------------------------
void set_soldier_on_map(tMap map, tPosition pos, tSoldier soldier) {
    if (map && pos && soldier 
        && is_position_on_map(pos)) {
            set_soldier_square(get_square(map, get_abcisse(pos), get_ordonnee(pos)), soldier);
    }
}

tSoldier clear_square_on_map(tMap map, tPosition pos) {
    return clear_square(get_square(map, get_abcisse(pos), get_ordonnee(pos)));
}

/*
 7 return cases :
    0 -> soldier indeed moved
    1 -> at least one of the pos is not on map
    2 -> posTo is not empty
    3 -> posFrom doesn't have a soldier
    4 -> posFrom has a soldier that can't move
    5 -> posFrom has a soldier that can not move over that distance
    6 -> Other
*/
int move_soldier_pos_to_pos(tMap map, tPosition posFrom, tPosition posTo) {
    int return_value = 6;
    if (!map || !posFrom || !posTo) {
        return return_value;
    }

    if (!(is_position_on_map(posFrom) && is_position_on_map(posTo))) {
        // one of the position is not on map
        return_value = 1;
    } else {
        if (!is_square_empty(get_square(map, get_abcisse(posTo), get_ordonnee(posTo)))) {
            // square to which soldier must move is not empty
            return_value = 2;
        } else {
            if (!get_soldier_square(get_square_from_pos(map, posFrom))) {
                // soldier NULL
                return_value = 3;
            } else {
                unsigned int soldiersMovement = get_movement(get_unit(get_soldier_square(get_square_from_pos(map, posFrom))));
                if (soldiersMovement == 0) {
                    // not a moveable soldier (flag or bomb)
                    return_value = 4;
                } else {
                    if (get_distance(posFrom, posTo) > soldiersMovement) {
                        // distance is higher than the soldier's movement
                        return_value = 5;
                    }
                }
            }
        }
    }


    return return_value;
}

// ------------------------------------ Destroyers ------------------------------------

void destroy_map(tMap *map) {
    if (map && *map) {
        for (unsigned int i = 0 ; i < NB_LINES ; ++i) {
            for (unsigned int j = 0 ; j < NB_COLUMNS ; ++j) {
                destroy_square(&(((*map)->squares)[i][j]));
            }
        }
        free(*map);
        *map = NULL;
    }
}
