#include <stdio.h>
#include <stdlib.h>
#include "stratego.h"
#include "army.h"
#include "map.h"
#include "position.h"

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
tSoldier get_soldier_user(tMap map, enum side_color side) {
    if (!map) return NULL;
    tPosition posWanted = NULL;
    tSoldier soldier = NULL;
    printf("Choisissez un soldat de votre camp à bouger :\n");
    int conds_ok = 0;
    do {
        posWanted = get_user_pos();
        soldier = get_soldier_square(get_square_from_pos(map, posWanted));
        conds_ok = soldier && (get_side(soldier) == side) && can_soldier_move(soldier);
        if (!conds_ok) {
            printf("Choisissez un soldat de votre couleur qui peut se déplacer.\n");
        }
    } while(!conds_ok);

    return soldier;
}

// Returns 0 if lost fight. 1 if moved (won the fight)
int manage_fight_with_movement(tMap map, tArmy armyBlue, tArmy armyRed, tSoldier soldierThatMoves, tSoldier soldierToFight) {
    int winner = soldier_fight(soldierThatMoves, soldierToFight);
    int does_move = 0;
    tArmy soldierMoverArmy = get_side(soldierThatMoves) == BLUE ? armyBlue : armyRed;
    tArmy soldierDefenderArmy = get_side(soldierToFight) == BLUE ? armyBlue : armyRed;
    switch (winner)
    {
    case 1:
        // soldierThatMoves wins, soldierToFight is removed, soldierThatMoves moves
        move_soldier_to_pos_2(map, soldierThatMoves, get_position(soldierToFight));
        destroy_soldier_in_army(soldierDefenderArmy, soldierToFight);
        does_move = 1;
        break;
    case 2:
        // soldierThatMoves lost, is removed and square get cleared
        clear_square_on_map(map, get_position(soldierThatMoves));
        destroy_soldier_in_army(soldierMoverArmy, soldierThatMoves);
        break;
    case 3:
        // Both soldiers are removed, both square are cleared.
        clear_square_on_map(map, get_position(soldierThatMoves));
        clear_square_on_map(map, get_position(soldierToFight));
        destroy_soldier_in_army(soldierMoverArmy, soldierThatMoves);
        destroy_soldier_in_army(soldierDefenderArmy, soldierToFight);
    default:
        break;
    }

    return does_move;
}

void play_a_turn(tMap map, tArmy armyBlue, tArmy armyRed, enum side_color who_plays) {
    tSoldier soldierToMove = get_soldier_user(map, who_plays);
    do {

    } while (get_movement(get_unit(soldierToMove)) == 0);

    tPosition posTargetted = NULL;
    int can_move_to_target = 0;
    char *name_target_soldier = get_name(get_unit(soldierToMove));
    
    // Choisir un soldat à déplacer
    printf("Chose position to which %s will move\n", name_target_soldier);
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
        manage_fight_with_movement(map, armyBlue, armyRed, soldierToMove, soldierOnPosToMove);
        break;
    default:
        printf("Error playing a turn.\n");
        break;
    }
    return;
}
