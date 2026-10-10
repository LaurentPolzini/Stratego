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
void set_lakes(tMap map);

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
    set_lakes(map);

    return map;
}

void set_lakes(tMap map) {
    set_state(get_square(map, 4, 2), LAKE);
    set_state(get_square(map, 4, 3), LAKE);
    set_state(get_square(map, 5, 2), LAKE);
    set_state(get_square(map, 5, 3), LAKE);

    set_state(get_square(map, 4, 6), LAKE);
    set_state(get_square(map, 4, 7), LAKE);
    set_state(get_square(map, 5, 6), LAKE);
    set_state(get_square(map, 5, 7), LAKE);
}

// ------------------------------------ Getters ------------------------------------
void print_map(tMap map) {
    if (map) {
        printf("\n");
        get_all_abreviations();
        for (int i = NB_LINES - 1 ; i >= 0 ; --i) {
            printf("%d ", i); // afficher les n° de lignes
            fflush(stdout);
            for (int j = 0 ; j < NB_COLUMNS ; ++j) {
                print_square(get_square(map, i, j));
            }
            printf("\n");
        }
        printf("  ");
        fflush(stdout);
        for (int j = 0 ; j < NB_COLUMNS ; ++j) {
            printf("  %d ", j); // afficher les n° de colonnes
            fflush(stdout);
        }
        printf("\n");
    }
}

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

// return if line and column given by pos is < 10.
int is_position_on_map(tPosition pos) {
    if (pos) {
        return (get_abcisse(pos) < NB_LINES)
            && (get_ordonnee(pos) < NB_COLUMNS);
    }
    return 0;
}

int is_square_on_map(tSquare square) {
    if (!square) return 0;
    return is_position_on_map(get_position_square(square));
}

// Is square part of the map
int is_soldier_on_map_same_as_square(tMap map, tSquare square) {
    if (!(map && square && is_square_on_map(square))) return 0;

    tPosition posSoldier = get_position_square(square);
    tSoldier soldier_square_from_map = get_soldier_square(get_square(map, get_abcisse(posSoldier), get_ordonnee(posSoldier)));
    return have_soldiers_same_id(soldier_square_from_map, get_soldier_square(square));
}

int is_soldier_on_map(tMap map, tSoldier soldier) {
    if (!(map && soldier)) return 0;
    tSoldier soldier_on_map = get_soldier_square(get_square_from_pos(map, get_position(soldier)));

    return have_soldiers_same_id(soldier_on_map, soldier);
}

// Can the soldier move from one square to another
/*

*/
int can_soldier_on_square_move_to_square(tMap map, tSquare squareFrom, tSquare squareTo) {
    if (!(map && squareFrom && squareTo
         && is_soldier_on_map_same_as_square(map, squareFrom))) return 0;

    int can_he = 0;




    return can_he;
}

// return 1 if can move to pos, 2 if fight, 0 in every other cases
int can_soldier_move_to_pos(tMap map, tSoldier soldier, tPosition pos) {
    if (!(map && soldier && pos && is_position_on_map(pos) && is_soldier_on_map(map, soldier) && can_soldier_move(soldier))) return 0;
    int ret_val = 0;
    tSquare square_on_pos = get_square_from_pos(map, pos);
    tSoldier soldier_on_pos = get_soldier_square(square_on_pos);

    if (soldier_on_pos 
        && !are_soldiers_on_same_side(soldier, soldier_on_pos)) {
        ret_val = 2; // fight !
    } else {
        int distance = get_distance(get_position(soldier), pos);
        if (distance > 0 && is_square_empty(square_on_pos) 
            && can_soldier_move_this_far(soldier, distance)) {
            // if square to move to is available and movement of soldier enough
            ret_val = 1;
        }
    }
    return ret_val;
}

// ------------------------------------ Setters ------------------------------------
int set_soldier_on_map(tMap map, tPosition pos, tSoldier soldier) {
    if (map && pos && soldier && is_position_on_map(pos)) {
        // If soldier is indeed set, and he isn't set for the first time,
        // it means he moves, so we need to clear square from where he comes
        
        return set_soldier_square(get_square(map, get_abcisse(pos), get_ordonnee(pos)), soldier);
    }
    return 0;
}

tSoldier clear_square_on_map(tMap map, tPosition pos) {
    return clear_square(get_square(map, get_abcisse(pos), get_ordonnee(pos)));
}

int move_soldier_to_pos_2(tMap map, tSoldier soldier, tPosition pos) {
    if (!(can_soldier_move_to_pos(map, soldier, pos) > 0)) return 0;

    tPosition posTmp = create_position(get_abcisse(get_position(soldier)), get_ordonnee(get_position(soldier)));
    int did_move = set_soldier_on_map(map, pos, soldier);
    if (did_move && is_position_on_map(posTmp)) {
        clear_square_on_map(map, posTmp);
    }
    destroy_position(&posTmp);
    return did_move;
}

tPosition move_soldier_to_pos(tMap map, tSoldier soldier, tPosition pos) {
    if (!(map && soldier && pos)) return NULL;
    tPosition posSoldier = get_position(soldier);
    switch (can_soldier_move_to_pos(map, soldier, pos))
    {
    case 0:
        return posSoldier;
        break;
    case 1:
        set_soldier_on_map(map, pos, soldier);
        return pos;
        break;
    case 2:
        {
        // fight !
        tSquare squareSoldierToFight = get_square_from_pos(map, pos);
        tSoldier soldierToFight = get_soldier_square(squareSoldierToFight);

        // in order to get @ of soldier1 if he is destroyed
        int winner = soldier_fight(soldier, soldierToFight);
        switch (winner)
        {
        case 1:
            // kills soldier2 and moves soldier1
            clear_square(squareSoldierToFight);
            destroy_soldier(&soldierToFight);
            set_soldier_on_map(map, pos, soldier);
            return get_position(soldier);
            break;
        case 2:
            {
            // clear moving soldier, he lost
            tSoldier soldierToDestroy = clear_square_on_map(map, posSoldier);
            destroy_soldier(&soldierToDestroy);
            break;
            }
        case 3:
            {
            // both unit died, clear square 1 and 2
            clear_square_on_map(map, posSoldier);
            tSoldier soldierToDestroy = clear_square_on_map(map, posSoldier);
            destroy_soldier(&soldierToFight);
            destroy_soldier(&soldierToDestroy);
            break;
            }
        default:
            break;
        }
        }
    default:
        break;
    }
    return posSoldier;
}

// ------------------------------------ Destroyers ------------------------------------

// Soldiers are destroyed in an other way.
void destroy_map(tMap *map) {
    if (map && *map) {
        for (unsigned int i = 0 ; i < NB_LINES ; ++i) {
            for (unsigned int j = 0 ; j < NB_COLUMNS ; ++j) {
                destroy_square(&(((*map)->squares)[i][j]));
            }
            free((*map)->squares[i]);
        }
        free((*map)->squares);
        free(*map);
        *map = NULL;
    }
}
