#include <stdio.h>
#include <stdlib.h>
#include "stratego.h"
#include "army.h"
#include "map.h"
#include "position.h"

struct sBoard {
    tMap map;
    tArmy armyBlue;
    tArmy armyRed;

    enum side_color playing_side;
};

// -------------------------------- CREATORS --------------------------------
tBoard create_board(tMap map, tArmy armyBlue, tArmy armyRed) {
    tBoard board = malloc(sizeof(struct sBoard));
    if (!board) {
        free(board);
        return NULL;
    }
    board->map = map;
    board->armyBlue = armyBlue;
    board->armyRed = armyRed;

    board->playing_side = RED;
    return board;
}

// -------------------------------- DESTROYERS --------------------------------
void destroy_board(tBoard *board) {
    if (board && *board) {
        destroy_army(&((*board)->armyBlue));
        destroy_army(&((*board)->armyRed));
        destroy_map(&((*board)->map));
        free(*board);
        *board = NULL;
    }
}


// -------------------------------- GETTERS --------------------------------
tMap get_board_map(tBoard board) {
    if (!board) return NULL;
    return board->map;
}

tArmy get_blue_army(tBoard board) {
    if (!board) return NULL;
    return board->armyBlue;
}

tArmy get_red_army(tBoard board) {
    if (!board) return NULL;
    return board->armyRed;
}

enum side_color get_playing_side(tBoard board) {
    if (!board) return BLUE;
    return board->playing_side;
}

void start_game(tMap map, tArmy armyBlue, tArmy armyRed) {
    if (!(map && armyBlue && armyRed)) return;

}

tPosition get_user_pos(void) {
    int is_pos_ok = 0;

    int abciss = OUT_OF_POS;
    int ordonne = OUT_OF_POS;
    tPosition pos = create_position(abciss, ordonne);
    printf("Entrez des coordonnées entre 0 et 9 :\n");
    do {
        printf("Abcisse Ordonnée : ");
        fflush(stdout);
        scanf("%d", &abciss);
        scanf("%d", &ordonne);

        set_abcisse(pos, abciss);
        set_ordonnee(pos, ordonne);

        is_pos_ok = is_position_on_map(pos);
        if (!is_pos_ok) {
            printf("Les coordonnées entrées sont incorrectes, elles doivent etre entre 0 et 9.\n\n");
        }
    } while (!is_pos_ok);

    return pos;
}

/*
    Pour choisir un soldat valide il faut remplir les conditions suivantes :
        - Un soldat à la position demandée
        - Un soldat de son armée (sa couleur)
        - Un soldat qui puisse bouger (movement > 0)
*/
tSoldier get_soldier_user(tMap map, tArmy army) {
    if (!map) return NULL;
    int how_many_can_move = 0;
    tSoldier *moveables = which_soldiers_can_move(map, army, &how_many_can_move);

    tPosition posWanted = NULL;
    tSoldier soldier = NULL;
    printf("Choisissez un soldat de votre camp à bouger :\n");
    int conds_ok = 0;
    do {
        posWanted = get_user_pos();
        soldier = get_soldier_square(get_square_from_pos(map, posWanted));
        conds_ok = soldier && (get_side(soldier) == get_army_color(army)) 
            && can_soldier_move(soldier) && is_soldier_moveable(map, moveables, how_many_can_move, soldier); 
        if (!conds_ok) {
            printf("Choisissez un soldat de votre couleur qui peut se déplacer.\n");
        }
    } while(!conds_ok);

    return soldier;
}

int is_soldier_moveable(tMap map, tSoldier *moveableSoldiers, int size, tSoldier soldier) {
    if (!(map && moveableSoldiers && soldier)) return 0;
    for (int i = 0 ; i < size ; ++i) {
        if (are_soldiers_equal(moveableSoldiers[i], soldier)) {
            return 1;
        }
    }
    return 0;
}

tSoldier *which_soldiers_can_move(tMap map, tArmy army, int *how_many_can_move) {
    if (!(map && army)) return NULL;
    tSoldier *soldierz = get_soldierZ_in_army(army);

    tSoldier *moveable_soldierzTMP = malloc(sizeof(tSoldier) * SIZE_ARMY);
    int ind_moveable = 0;

    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        if (soldierz[i]) {
            if (does_have_moveable_squares(map, soldierz[i])) {
                moveable_soldierzTMP[ind_moveable++] = soldierz[i];
            }
        }
    }
    tSoldier *moveable_soldierz = malloc(sizeof(tSoldier) * (ind_moveable + 1));
    for (int i = 0 ; i < ind_moveable + 1 ; ++i) {
        moveable_soldierz[i] = moveable_soldierzTMP[i];
    }
    free(moveable_soldierzTMP);
    if (how_many_can_move) {
        *how_many_can_move = ind_moveable;
    }
    return moveable_soldierz;
}


// -------------------------------- PLAY --------------------------------
// Returns 0 if lost fight. 1 if moved (won the fight)
int manage_fight_with_movement(tBoard board, tSoldier soldierThatMoves, tSoldier soldierToFight) {
    int winner = soldier_fight(soldierThatMoves, soldierToFight);
    int does_move = 0;
    tArmy soldierMoverArmy = get_side(soldierThatMoves) == BLUE ? board->armyBlue : board->armyRed;
    tArmy soldierDefenderArmy = get_side(soldierToFight) == BLUE ? board->armyBlue : board->armyRed;
    switch (winner)
    {
    case 1:
        // soldierThatMoves wins, soldierToFight is removed, soldierThatMoves moves
        move_soldier_to_pos_2(board->map, soldierThatMoves, get_position(soldierToFight));
        destroy_soldier_in_army(soldierDefenderArmy, soldierToFight);
        does_move = 1;
        break;
    case 2:
        // soldierThatMoves lost, is removed and square get cleared
        clear_square_on_map(board->map, get_position(soldierThatMoves));
        destroy_soldier_in_army(soldierMoverArmy, soldierThatMoves);
        break;
    case 3:
        // Both soldiers are removed, both square are cleared.
        clear_square_on_map(board->map, get_position(soldierThatMoves));
        clear_square_on_map(board->map, get_position(soldierToFight));
        destroy_soldier_in_army(soldierMoverArmy, soldierThatMoves);
        destroy_soldier_in_army(soldierDefenderArmy, soldierToFight);
    default:
        break;
    }

    return does_move;
}

void play_a_turn(tBoard board) {
    if (!board) return;
    printf("\n");
    print_color(board->playing_side);
    printf("is up to play !\n");
    tMap map = board->map;
    tArmy armyBlue = board->armyBlue;
    tArmy armyRed = board->armyRed;

    tSoldier soldierToMove = get_soldier_user(map, (board->playing_side == BLUE ? armyBlue : armyRed));
    do {

    } while (get_movement(get_unit(soldierToMove)) == 0);

    tPosition posTargetted = NULL;
    int can_move_to_target = 0;
    char *name_target_soldier = get_name(get_unit(soldierToMove));
    
    // Choisir un soldat à déplacer
    printf("\nChose position to which %s will move\n", name_target_soldier);
    do {
        posTargetted = get_user_pos();
        can_move_to_target = can_soldier_move_to_pos(map, soldierToMove, posTargetted);
        if (!can_move_to_target) {
            printf("Please chose a position to where your %s can move to.\n", name_target_soldier);
        }
    } while(!can_move_to_target);
    tSoldier soldierOnPosToMove = get_soldier_square(get_square_from_pos(map, posTargetted));
    switch (can_move_to_target)
    {
    case 1: // normal move
        /* code */
        if (move_soldier_to_pos_2(map, soldierToMove, posTargetted)) {
            printf("%s moved to %d %d\n", name_target_soldier, get_abcisse(posTargetted), get_ordonnee(posTargetted));
        } else {
            printf("%s couldn't move to %d %d\n", name_target_soldier, get_abcisse(posTargetted), get_ordonnee(posTargetted));
        }
        break;
    case 2: // fight
        printf("Fight between %s and %s\n", name_target_soldier, get_name(get_unit(get_soldier_square(get_square_from_pos(map, posTargetted)))));
        manage_fight_with_movement(board, soldierToMove, soldierOnPosToMove);
        break;
    default:
        printf("Error playing a turn.\n");
        break;
    }
    board->playing_side = (board->playing_side == BLUE ? RED : BLUE);

    return;
}
