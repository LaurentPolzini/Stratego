#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stratego.h"
#include "army.h"
#include "map.h"
#include "position.h"
#include "robot.h"

struct sBoard {
    tMap map;
    tArmy armyBlue;
    tArmy armyRed;

    char *red_player_name;
    char *blue_player_name;

    enum side_color playing_side;
};

void set_red_name(tBoard board, char *name);
void set_blue_name(tBoard board, char *name);

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

    board->red_player_name = malloc(sizeof(char) * 25);
    board->blue_player_name = malloc(sizeof(char) * 25);

    board->playing_side = RED;
    return board;
}

// -------------------------------- DESTROYERS --------------------------------
void destroy_board(tBoard *board) {
    if (board && *board) {
        destroy_army(&((*board)->armyBlue));
        destroy_army(&((*board)->armyRed));
        destroy_map(&((*board)->map));
        free((*board)->blue_player_name);
        free((*board)->red_player_name);
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

void start_game(tBoard board) {
    if (!board) return;

}

tPosition get_user_pos(void) {
    int is_pos_ok = 0;
    char input[10];

    int abciss = OUT_OF_POS;
    int ordonne = OUT_OF_POS;
    tPosition pos = create_position(abciss, ordonne);
    printf("Entrez des coordonnées entre 0 et 9 :\n");
    do {
        printf("Abcisse Ordonnée (ex: 85 ou 8 5): ");
        fflush(stdout);
        scanf("%s", input);

        int indTmp = 0;
        while (input[indTmp] != '\0') {
            if ((input[indTmp] >= '0') && (input[indTmp] <= '9')) {
                if (abciss == OUT_OF_POS) {
                    abciss = input[indTmp] - 48; // 0 in ascii
                } else {
                    if (ordonne == OUT_OF_POS) {
                        ordonne = input[indTmp] - 48;
                    } else {
                        break;
                    }
                }
            }
            ++indTmp;
        }

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
    Pour choisir un soldat valide a bouger il faut remplir les conditions suivantes :
        - Un soldat à la position demandée
        - Un soldat de son armée (sa couleur)
        - Un soldat qui puisse bouger (movement > 0)
*/
tSoldier get_soldier_user(tMap map, tArmy army) {
    if (!map) return NULL;
    int how_many_can_move = 0;
    tSoldier *moveables = which_soldiers_can_move(map, army, &how_many_can_move);
    if (how_many_can_move == 0) {
        printf("You don't have any moveable soldier. You lose.\n");
        return NULL;
    }

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

    destroy_position(&posWanted);
    free(moveables);
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

void print_settable_soldierz(int *pickable_soldiers, tArmy army) {
    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        if (pickable_soldiers[i]) {
            printf("%d - %s\n", i, get_name(get_unit(get_soldier_in_army(army, i))));
        }
    }
}

// returns id
int pick_soldier(int *pickable_soldiers, tArmy army) {
    if (!(pickable_soldiers && army)) return 50;
    int chosen_id = 50;
    int cond_filled = 0;
    do {
        print_settable_soldierz(pickable_soldiers, army);
        printf("Choose your soldier to set (enter id) : ");
        scanf("%d", &chosen_id);
        cond_filled = (chosen_id >= 0) && (chosen_id < SIZE_ARMY) && pickable_soldiers[chosen_id];
        if (!cond_filled) {
            printf("Please pick and id between 0 and 39 for the printed soldiers.\n");
        }
    } while (!cond_filled);

    return chosen_id;
}

// returns 1 or 2 for the one that will play red army (first player).
int get_first_player(void) {
    return (rand() % 2) + 1;
}

char *get_red_name(tBoard board) {
    if (!board) return NULL;
    return board->red_player_name;
}

char *get_blue_name(tBoard board) {
    if (!board) return NULL;
    return board->blue_player_name;
}

// -------------------------------- SETTERS --------------------------------
// while not 40 soldiers are set :
/*
    Pick a square on your side of the map
    If picked square has a soldier on it, remove it.
    Pick a soldier to set
    Set the soldier.
*/
void set_army_on_map(tBoard board, enum side_color side) {
    if (!board) return;
    tArmy army_to_set = side == BLUE ? board->armyBlue : board->armyRed;
    int nb_soldier_set = 0;
    tPosition posChosen = NULL;
    int cond_filled = 0;
    int *settable_soldierz = malloc(SIZE_ARMY * sizeof(int));
    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        settable_soldierz[i] = 1; // all soldiers are settable at the initialization of the game
    }

    int idSoldierToSet = 50;
    int yes_or_no = 0;
    do {
        do { // pick a square to place soldier on, or remove one.
            print_hidden_map(board->map, side);
            posChosen = get_user_pos();
            cond_filled = BLUE ? (get_abcisse(posChosen) < 4) : (get_abcisse(posChosen) > 5);
            if (!cond_filled) {
                printf("\n /!\\ Please pick a square on your side of the map. /!\\\n");
            }
        } while(!cond_filled);
        // if picked pos is occupied, remove current soldier to place another
        if (is_square_occupied(get_square_from_pos(board->map, posChosen))) {
            settable_soldierz[get_id(get_soldier_square(get_square_from_pos(board->map, posChosen)))] = 1; // settable again
            clear_square_on_map(board->map, posChosen);
            --nb_soldier_set;
            print_hidden_map(board->map, side);
        }
        idSoldierToSet = pick_soldier(settable_soldierz, army_to_set);
        settable_soldierz[idSoldierToSet] = 0;
        set_soldier_on_map(board->map, posChosen, get_soldier_in_army(army_to_set, idSoldierToSet));
        ++nb_soldier_set;

        destroy_position(&posChosen);

        if (nb_soldier_set == 40) {
            print_hidden_map(board->map, side);
            printf("Is your whole army in place ? (yes : 1, no : 0) : ");
            scanf("%d", &yes_or_no);
        }
    } while(!(yes_or_no == 1));

    free(settable_soldierz);
    settable_soldierz = NULL;
}

void set_next_side(tBoard board) {
    if (!board) return;
    board->playing_side = (board->playing_side == BLUE ? RED : BLUE);
}

void set_red_name(tBoard board, char *name) {
    if (!board) return;
    strcpy(board->red_player_name, name);
}

void set_blue_name(tBoard board, char *name) {
    if (!board) return;
    strcpy(board->blue_player_name, name);
}

// -------------------------------- PLAY --------------------------------
void play_all_game(tBoard board) {
    if (!board) return;
    int fp = get_first_player();

    char *name1 = malloc(sizeof(char) * 25);
    printf("Please enter your name (<25 chararacters) : ");
    scanf("%s", name1);
    printf("Ok-\n");

    char *name2 = malloc(sizeof(char) * 25);
    printf("Please enter your name (<25 chararacters) : ");
    scanf("%s", name2);

    set_red_name(board, (fp == 1 ? name1 : name2));
    set_blue_name(board, (fp == 1 ? name1 : name2));

    free(name1);
    free(name2);

    //set_army_on_map(board, RED);
    //set_army_on_map(board, BLUE);

    // FOR TESTS !!!!!!!!!
    set_whole_blue_army_on_map(get_board_map(board), get_blue_army(board));
    set_whole_red_army_on_map(get_board_map(board), get_red_army(board));

    print_hidden_map(board->map, board->playing_side);
    while (!play_a_turn(board)) {
        set_next_side(board);
        print_hidden_map(board->map, board->playing_side);
    }
    print_color(board->playing_side);
    printf("%s won the game !!! Well played !!\n", (board->playing_side == BLUE ? board->blue_player_name : board->red_player_name));
}


// Returns 0 if lost fight. 1 if moved (won the fight)
int manage_fight_with_movement(tBoard board, tSoldier soldierThatMoves, tSoldier soldierToFight) {
    if (!(board && soldierThatMoves && soldierToFight)) return -1;
    int does_move = 0;
    tArmy soldierMoverArmy = get_side(soldierThatMoves) == BLUE ? board->armyBlue : board->armyRed;
    tArmy soldierDefenderArmy = get_side(soldierToFight) == BLUE ? board->armyBlue : board->armyRed;
    int winner = soldier_fight(soldierThatMoves, soldierToFight);

    tPosition posMover = create_position(OUT_OF_POS, OUT_OF_POS);
    copy_pos(get_position(soldierThatMoves), posMover);
    tPosition posDefender = create_position(OUT_OF_POS, OUT_OF_POS);
    copy_pos(get_position(soldierToFight), posDefender);

    switch (winner)
    {
    case 1:
        // soldierThatMoves wins, soldierToFight is removed, soldierThatMoves moves
        destroy_soldier_in_army(soldierDefenderArmy, clear_square_on_map(board->map, posDefender));// Before because move soldier sets 
        // square->soldier = soldierThatMoves
        // but square->soldier = soldierDefender.
        // So now we have soldierDefender = soldierThatMoves
        move_soldier_to_pos(board->map, soldierThatMoves, posDefender);
        does_move = 1;
        break;
    case 2:
        // soldierThatMoves lost, is removed and square get cleared
        destroy_soldier_in_army(soldierMoverArmy, clear_square_on_map(board->map, posMover));
        break;
    case 3:
        // Both soldiers are removed, both square are cleared.
        destroy_soldier_in_army(soldierMoverArmy, clear_square_on_map(board->map, posMover));
        destroy_soldier_in_army(soldierDefenderArmy, clear_square_on_map(board->map, posDefender));
        break;
    default:
        break;
    }
    destroy_position(&posMover);
    destroy_position(&posDefender);

    return does_move;
}

// returns if flag captured
int play_a_turn(tBoard board) {
    if (!board) return 0;
    int ret_val = 0;
    printf("\n%s - ", (board->playing_side == BLUE ? board->blue_player_name : board->red_player_name));
    fflush(stdout);
    print_color(board->playing_side);
    printf("is up to play !\n");
    tMap map = board->map;

    tArmy armyToMove = board->playing_side == BLUE ? board->armyBlue : board->armyRed;

    tSoldier soldierToMove = get_soldier_user(map, armyToMove);
    if (soldierToMove == NULL) {
        // Not any moveable soldier.
        return 2;
    }
    tPosition posBefore = create_position(OUT_OF_POS, OUT_OF_POS);
    copy_pos(get_position(soldierToMove), posBefore);

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
    ret_val = is_flag(get_unit(soldierOnPosToMove));

    switch (can_move_to_target)
    {
    case 1: // normal move
        if (move_soldier_to_pos(map, soldierToMove, posTargetted)) {
            printf("%s moved from %d %d to %d %d\n", name_target_soldier, get_abcisse(posBefore), get_ordonnee(posBefore), get_abcisse(posTargetted), get_ordonnee(posTargetted));
        } else {
            printf("%s couldn't move to %d %d\n", name_target_soldier, get_abcisse(posTargetted), get_ordonnee(posTargetted));
        }
        break;
    case 2: // fight
        printf("\n-> Fight between %s and %s\n", name_target_soldier, get_name(get_unit(get_soldier_square(get_square_from_pos(map, posTargetted)))));
        manage_fight_with_movement(board, soldierToMove, soldierOnPosToMove);
        break;
    default:
        printf("Error playing a turn.\n");
        break;
    }

    destroy_position(&posBefore);
    destroy_position(&posTargetted);

    return ret_val;
}

int play_robot_turn(tBoard board) {
    if (!board) return 0;
    int ret_val = 0;
    printf("\n%s - ", (board->playing_side == BLUE ? board->blue_player_name : board->red_player_name));
    fflush(stdout);
    print_color(board->playing_side);
    printf("is up to play !\n");
    tMap map = board->map;

    tArmy armyToMove = board->playing_side == BLUE ? board->armyBlue : board->armyRed;

    tSoldier soldierToMove = NULL;
    tSquare squareTargetted = NULL;
    random_soldier_to_square(map, armyToMove, &soldierToMove, &squareTargetted);
    if (soldierToMove == NULL || squareTargetted == NULL) {
        printf("You don't have any moveable soldier, you lose the game.\n");
        return 2;
    }

    tPosition posBefore = create_position(OUT_OF_POS, OUT_OF_POS);
    copy_pos(get_position(soldierToMove), posBefore);

    tPosition posTargetted = get_position_square(squareTargetted);

    char *name_target_soldier = get_name(get_unit(soldierToMove));
    
    tSoldier soldierToEventuallyfight = get_soldier_square(squareTargetted);

    ret_val = is_flag(get_unit(soldierToEventuallyfight));

    switch (can_soldier_move_to_pos(map, soldierToMove, posTargetted))
    {
    case 1: // normal move
        if (move_soldier_to_pos(map, soldierToMove, get_position_square(squareTargetted))) {
            printf("%s moved from %d %d to %d %d\n", name_target_soldier, get_abcisse(posBefore), get_ordonnee(posBefore), get_abcisse(posTargetted), get_ordonnee(posTargetted));
        } else {
            printf("%s couldn't move to %d %d\n", name_target_soldier, get_abcisse(posTargetted), get_ordonnee(posTargetted));
        }
        break;
    case 2: // fight
        printf("\n-> Fight between %s and %s on square %d %d\n", name_target_soldier, get_name(get_unit(get_soldier_square(get_square_from_pos(map, posTargetted)))), get_abcisse(posTargetted), get_ordonnee(posTargetted));
        manage_fight_with_movement(board, soldierToMove, soldierToEventuallyfight);
        if (!is_square_empty(get_square_from_pos(board->map, posBefore))) {
            destroy_position(&posBefore);
            return 2;
        }
        break;
    default:
        printf("Error playing a turn.\n");
        break;
    }
    destroy_position(&posBefore);
    return ret_val;
}

void play_all_game_vs_robot(tBoard board) {
    if (!board) return;
    int fp = get_first_player();

    char *name1 = malloc(sizeof(char) * 25);
    printf("Please enter your name (<25 chararacters) : ");
    scanf("%s", name1);
    printf("Ok-\n");

    char *name2 = "robot";

    set_red_name(board, (fp == 1 ? name1 : name2));
    set_blue_name(board, (fp == 2 ? name1 : name2));

    free(name1);

    //set_army_on_map(board, RED);
    //set_army_on_map(board, BLUE);

    // FOR TESTS !!!!!!!!
    if (fp == 1) {
        set_whole_red_army_on_map(get_board_map(board), get_red_army(board));
        set_army_randomly(get_board_map(board), get_blue_army(board));
    } else {
        set_whole_blue_army_on_map(get_board_map(board), get_blue_army(board));
        set_army_randomly(get_board_map(board), get_red_army(board));
    }

    print_hidden_map(board->map, board->playing_side);

    int went_well = 0;
    while(!went_well) {
        if (fp == 1) {
            went_well = play_a_turn(board);
        } else {
            went_well = play_robot_turn(board);
        }
        if (went_well == 2) {
            printf("Game ends abruptly, error.\n");
        }
        set_next_side(board);
        print_hidden_map(board->map, board->playing_side);
        fp = (fp % 2) + 1;
    }
    set_next_side(board);
    print_color(board->playing_side);
    printf("%s won the game !!! Well played !!\n", (board->playing_side == BLUE ? board->blue_player_name : board->red_player_name));
}
