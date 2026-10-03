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

tSquare get_square(tMap map, unsigned int i, unsigned int j) {
    if (map && (i < NB_LINES) && (j < NB_COLUMNS)) {
        return (map->squares)[i][j];
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
