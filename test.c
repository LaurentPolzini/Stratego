#include <stdio.h>
#include <stdlib.h>
#include "unite.h"
#include "army.h"
#include "map.h"
#include "position.h"
#include "square.h"
#include "stratego.h"

/*
    --------------------------------------- UNIT TEST ---------------------------------------
*/
int test_fight_marshall_general(void) {
    int nb_error = 0;
    tUnite marshall = create_marshall();
    tUnite general = create_general();

    if (who_wins(marshall, general) != 1) {
        printf("\tError - fight marshall (must win) vs general\n");
        ++nb_error;
    }
    destroy_unit(&marshall);
    destroy_unit(&general);
    if (!marshall && !general) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_marshall_bomb(void) {
    int nb_error = 0;
    tUnite marshall = create_marshall();
    tUnite bomb = create_bomb();

    if (who_wins(marshall, bomb) != 2) {
        printf("\tError - fight marshall vs bomb (must win)\n");
        ++nb_error;
    }
    destroy_unit(&marshall);
    destroy_unit(&bomb);
    if (!marshall && !bomb) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_miner_bomb(void) {
    int nb_error = 0;
    tUnite miner = create_miner();
    tUnite bomb = create_bomb();

    if (who_wins(miner, bomb) != 1) {
        printf("\tError - fight miner (must win) vs bomb\n");
        ++nb_error;
    }
    destroy_unit(&miner);
    destroy_unit(&bomb);
    if (!miner && !bomb) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_miner_flag(void) {
    int nb_error = 0;
    tUnite miner = create_miner();
    tUnite flag = create_flag();

    if (who_wins(miner, flag) != 1) {
        printf("\tError - fight miner (must win) vs flag\n");
        ++nb_error;
    }
    destroy_unit(&miner);
    destroy_unit(&flag);
    if (!miner && !flag) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_scout_flag(void) {
    int nb_error = 0;
    tUnite scout = create_scout();
    tUnite flag = create_flag();

    if (who_wins(scout, flag) != 1) {
        printf("\tError - fight scout (must win) vs flag\n");
    }
    destroy_unit(&scout);
    destroy_unit(&flag);
    if (!scout && !flag) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_scout_scout(void) {
    int nb_error = 0;
    tUnite scout1 = create_scout();
    tUnite scout2 = create_scout();

    if (who_wins(scout1, scout2) != 3) {
        printf("\tError - scouts fight. Both must die\n");
        ++nb_error;
    }
    destroy_unit(&scout1);
    destroy_unit(&scout2);
    if (!scout1 && !scout2) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_colonel_marshall(void) {
    int nb_error = 0;
    tUnite colonel = create_colonel();
    tUnite marshall = create_marshall();

    if (who_wins(colonel, marshall) != 2) {
        printf("\tError - fight colonel vs marshall (must win)\n");
        ++nb_error;
    }
    destroy_unit(&colonel);
    destroy_unit(&marshall);
    if (!colonel && !marshall) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_spy_spy(void) {
    int nb_error = 0;
    tUnite spy1 = create_spy();
    tUnite spy2 = create_spy();

    if (who_wins(spy1, spy2) != 3) {
        printf("\tError - fight spy vs spy (both killed)\n");
        ++nb_error;
    }
    destroy_unit(&spy1);
    destroy_unit(&spy2);
    if (!spy1 && !spy2) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_spy_marshall(void) {
    int nb_error = 0;
    tUnite spy = create_spy();
    tUnite marshall = create_marshall();

    if (who_wins(spy, marshall) != 1) {
        printf("\tError - fight spy (must win) vs marshall\n");
        ++nb_error;
    }
    destroy_unit(&spy);
    destroy_unit(&marshall);
    if (!spy && !marshall) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_spy_bomb(void) {
    int nb_error = 0;
    tUnite spy = create_spy();
    tUnite bomb = create_bomb();

    if (who_wins(spy, bomb) != 2) {
        printf("\tError - fight spy vs bomb(must win)\n");
        ++nb_error;
    }
    destroy_unit(&spy);
    destroy_unit(&bomb);
    if (!spy && !bomb) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_spy_scout(void) {
    int nb_error = 0;
    tUnite spy = create_spy();
    tUnite scout = create_scout();

    if (who_wins(spy, scout) != 2) {
        printf("\tError - fight spy vs scout(must win)\n");
        ++nb_error;
    }
    destroy_unit(&spy);
    destroy_unit(&scout);
    if (!spy && !scout) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

int test_fight_marshall_spy(void) {
    int nb_error = 0;
    tUnite spy = create_spy();
    tUnite marshall = create_marshall();

    if (who_wins(marshall, spy) != 2) {
        printf("\tError - fight marshall vs spy (must win)\n");
        ++nb_error;
    }
    destroy_unit(&spy);
    destroy_unit(&marshall);
    if (!spy && !marshall) {
        return nb_error;
    }
    printf("\tError - Destroy unit gone wrong\n");
    ++nb_error;
    return nb_error;
}

// creates a unit. Is the unit the actual unit ?
int test_creators_comparators(void) {
    int nb_error = 0;
    tUnite spy = create_spy();
    if (!is_spy(spy)) {
        printf("\tError - spy creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&spy);
    if (spy) {
        printf("\tError - Spy Destruction didn't work\n");
        ++nb_error;
    }

    tUnite scout = create_scout();
    if (!is_scout(scout)) {
        printf("\tError - scout creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&scout);
    if (scout) {
        printf("\tError - Scout Destruction didn't work\n");
        ++nb_error;
    }

    tUnite miner = create_miner();
    if (!is_miner(miner)) {
        printf("\tError - miner creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&miner);
    if (miner) {
        printf("\tError - Miner Destruction didn't work\n");
        ++nb_error;
    }
    

    tUnite sergeant = create_sergeant();
    if (!is_sergeant(sergeant)) {
        printf("\tError - sergeant creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&sergeant);
    if (sergeant) {
        printf("\tError - Sergeant Destruction didn't work\n");
        ++nb_error;
    }

    tUnite lieutenant = create_lieutenant();
    if (!is_lieutenant(lieutenant)) {
        printf("\tError - lieutenant creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&lieutenant);
    if (lieutenant) {
        printf("\tError - Lieutenant Destruction didn't work\n");
        ++nb_error;
    }

    tUnite captain = create_captain();
    if (!is_captain(captain)) {
        printf("\tError - captain creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&captain);
    if (captain) {
        printf("\tError - Captain Destruction didn't work\n");
        ++nb_error;
    }

    tUnite major = create_major();
    if (!is_major(major)) {
        printf("\tError - major creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&major);
    if (major) {
        printf("\tError - Major Destruction didn't work\n");
        ++nb_error;
    }

    tUnite colonel = create_colonel();
    if (!is_colonel(colonel)) {
        printf("\tError - colonel creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&colonel);
    if (colonel) {
        printf("\tError - Colonel Destruction didn't work\n");
        ++nb_error;
    }

    tUnite general = create_general();
    if (!is_general(general)) {
        printf("\tError - general creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&general);
    if (general) {
        printf("\tError - General Destruction didn't work\n");
        ++nb_error;
    }

    tUnite marshall = create_marshall();
    if (!is_marshall(marshall)) {
        printf("\tError - marshall creators wrong\n");
    }
    destroy_unit(&marshall);
    if (marshall) {
        printf("\tError - Marshall Destruction didn't work\n");
        ++nb_error;
    }
    
    tUnite bomb = create_bomb();
    if (!is_bomb(bomb)) {
        printf("\tError - bomb creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&bomb);
    if (bomb) {
        printf("\tError - Bomb Destruction didn't work\n");
        ++nb_error;
    }

    tUnite flag = create_flag();
    if (!is_flag(flag)) {
        printf("\tError - flag creators wrong\n");
        ++nb_error;
    }
    destroy_unit(&flag);
    if (flag) {
        printf("\tError - Flag Destruction didn't work\n");
        ++nb_error;
    }

    return nb_error;
}


/*
    --------------------------------------- ARMY TEST ---------------------------------------
*/
int test_creation_destruction_soldier(void) {
    int nb_error = 0;
    tSoldier soldier = create_soldier(create_spy(), BLUE, 0);
    if (!(is_spy(get_unit(soldier)))) {
        printf("\tError - Soldier is supposed to be spy\n");
        ++nb_error;
    }
    if (!(get_side(soldier) == BLUE)) {
        printf("\tError - Soldier is on Blue side\n");
        ++nb_error;
    }
    if (!(get_id(soldier) == 0)) {
        printf("\tError - Soldier id is 0\n");
        ++nb_error;
    }
    if (!(get_abcisse(get_position(soldier)) == OUT_OF_POS)) {
        printf("\tError - Soldier abcisse is not %d (=>%d)\n", OUT_OF_POS, get_abcisse(get_position(soldier)));
        ++nb_error;
    }
    if (!(get_ordonnee(get_position(soldier)) == OUT_OF_POS)) {
        printf("\tError - Soldier ordonnee is not %d (=>%d)\n", OUT_OF_POS, get_ordonnee(get_position(soldier)));
        ++nb_error;
    }
    printf("Destruction.\n");
    destroy_soldier(&soldier);
    if (soldier || get_unit(soldier)) {
        printf("\tError - soldier not destroyed\n");
        ++nb_error;
    }
    return nb_error;
}

int test_creation_army(void) {
    int nb_error = 0;

    tArmy army = create_army(BLUE);

    int nb_flag = NB_FLAG; // must be 1
    int nb_bomb = NB_BOMB; // must be 6
    int nb_marshall = NB_MARSHALL; // must be 1
    int nb_general = NB_GENERAL; // must be 1
    int nb_spy = NB_SPY; // must be 1
    int nb_colonel = NB_COLONEL; // must be 2
    int nb_major = NB_MAJOR; // must be 3
    int nb_captain = NB_CAPTAIN; // must be 4
    int nb_lieutenant = NB_LIEUTENANT; // must be 4
    int nb_sergeant = NB_SERGEANT; // must be 4
    int nb_miner = NB_MINER; // must be 5
    int nb_scout = NB_SCOUT; // must be 8

    tSoldier *soldiers = get_soldierZ_in_army(army);
    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        if (!soldiers[i]) {
            printf("\tError - Not %d soldiers in army.\n", SIZE_ARMY);
            ++nb_error;
        } else {
            if (is_flag(get_unit(soldiers[i]))) {
                --nb_flag;
            }
            if (is_bomb(get_unit(soldiers[i]))) {
                --nb_bomb;
            }
            if (is_marshall(get_unit(soldiers[i]))) {
                --nb_marshall;
            }
            if (is_general(get_unit(soldiers[i]))) {
                --nb_general;
            }
            if (is_spy(get_unit(soldiers[i]))) {
                --nb_spy;
            }
            if (is_colonel(get_unit(soldiers[i]))) {
                --nb_colonel;
            }
            if (is_major(get_unit(soldiers[i]))) {
                --nb_major;
            }
            if (is_captain(get_unit(soldiers[i]))) {
                --nb_captain;
            }
            if (is_lieutenant(get_unit(soldiers[i]))) {
                --nb_lieutenant;
            }
            if (is_sergeant(get_unit(soldiers[i]))) {
                --nb_sergeant;
            }
            if (is_miner(get_unit(soldiers[i]))) {
                --nb_miner;
            }
            if (is_scout(get_unit(soldiers[i]))) {
                --nb_scout;
            }
        }
    }

    if (nb_flag || nb_bomb || nb_marshall || nb_general || nb_spy 
        || nb_colonel || nb_major || nb_captain || nb_lieutenant
        || nb_sergeant || nb_miner || nb_scout) {
            printf("\tError - Nombre dans l'armée incorrect\n");
            ++nb_error;
    }

    printf("Destruction army.\n");
    destroy_army(&army);
    if (army) {
        printf("\tError - Destruction didn't work\n");
        ++nb_error;
    }

    return nb_error;
}

/*
    --------------------------------------- POSITION TEST ---------------------------------------
*/
int test_position(void) {
    int nb_error = 0;

    tPosition pos = create_position(0, 20);
    if (get_abcisse(pos) != 0) {
        ++nb_error;
        printf("Error - Abcisse should be 0 (%d)\n", get_abcisse(pos));
    }
    if (get_ordonnee(pos) != 20) {
        ++nb_error;
        printf("Error - Ordonnee should be 20 (%d)\n", get_ordonnee(pos));
    }
    destroy_position(&pos);
    if (pos) {
        ++nb_error;
        printf("Error - Position wrongly destroyed\n");
    }

    return nb_error;   
}

int test_distance(void) {
    int nb_error = 0;

    tPosition posFrom = create_position(0, 0);
    tPosition posTo = create_position(0, 0);

    if (get_distance(posFrom, posTo) != 0) {
        ++nb_error;
        printf("Error - Distance should be 0.\n");
    }
    // --- next test
    set_ordonnee(posFrom, 0);
    set_abcisse(posFrom, 0);
    set_ordonnee(posTo, 0);
    set_abcisse(posTo, 9);

    if (get_distance(posFrom, posTo) != 9) {
        ++nb_error;
        printf("Error - Distance should be 0.\n");
    }

    // --- next test
    set_ordonnee(posFrom, 0);
    set_abcisse(posFrom, 0);
    set_ordonnee(posTo, 1);
    set_abcisse(posTo, 1);

    if (get_distance(posFrom, posTo) != UINT32_MAX) {
        ++nb_error;
        printf("Error - Distance should be %d. Not aligned\n", UINT32_MAX);
    }

    // --- next test
    set_ordonnee(posFrom, 2);
    set_abcisse(posFrom, 0);
    set_ordonnee(posTo, 0);
    set_abcisse(posTo, 1);

    if (get_distance(posFrom, posTo) != UINT32_MAX) {
        ++nb_error;
        printf("Error - Distance should be %d. Not aligned\n", UINT32_MAX);
    }

    destroy_position(&posFrom);
    destroy_position(&posTo);

    return nb_error;
}

/*
    --------------------------------------- SQUARE TEST ---------------------------------------
*/
int test_square(void) {
    int nb_error = 0;

    tSquare square = create_square(0, 9);
    if (get_soldier_square(square)) {
        ++nb_error;
        printf("Error - No soldier should be here\n");
    }
    if (get_state_square(square) != EMPTY) {
        ++nb_error;
        printf("Error - Square should be empty (state square\n");
    }
    if (get_abcisse(get_position_square(square)) != 0) {
        ++nb_error;
        printf("Error - Abcisse should be 0\n");
    }
    if (get_ordonnee(get_position_square(square)) != 9) {
        ++nb_error;
        printf("Error - Ordonnee should be 9\n");
    }
    if (!is_square_empty(square)) {
        ++nb_error;
        printf("Error - Square should be empty (is_empty)\n");
    }

    tSoldier soldat = create_soldier(create_captain(), BLUE, 0);
    set_soldier_square(square, soldat);
    if (!is_captain(get_unit(get_soldier_square(square)))) {
        ++nb_error;
        printf("Error - Captain should be on square\n");
    }
    if (is_square_empty(square)) {
        ++nb_error;
        printf("Error - Square shouldn't be empty, captain is on now !\n");
    }
    tSoldier cleared_soldier = clear_square(square);
    if (!is_captain(get_unit(cleared_soldier))) {
        ++nb_error;
        printf("Error - Cleared square should return captain unit\n");
    }
    if (!is_square_empty(square)) {
        ++nb_error;
        printf("Error - square should be emptied\n");
    }
    destroy_square(&square);
    if (square) {
        ++nb_error;
        printf("Error - Squared not destroyed\n");
    }
    if (!soldat) {
        ++nb_error;
        printf("Error - soldier should not be NULL\n");
    }
    destroy_soldier(&soldat);
    return nb_error;
}

/*
    --------------------------------------- MAP TEST ---------------------------------------
*/
int test_map(void) {
    int nb_error = 0;

    tMap map = create_map();

    tSquare **squares = get_map(map);
    for (int i = 0 ; i < NB_LINES ; ++i) {
        for (int j = 0 ; j < NB_COLUMNS ; ++j) {
            if (!(is_square_empty(squares[i][j]) || is_square_lake(squares[i][j]))) {
                ++nb_error;
                printf("Error - Square should be empty (map creation)\n");
            }
        }
    }
    
    if (squares[9][9] != get_square(map, 9, 9)) {
        ++nb_error;
        printf("Error - Not the same square (should be the same)\n");
    }
    tPosition pos = create_position(9, 12);
    if (is_position_on_map(pos)) {
        ++nb_error;
        printf("Error - Position 9 12 should not be on map\n");
    }
    destroy_position(&pos);

    pos = create_position(0, 5);
    if (!is_position_on_map(pos)) {
        ++nb_error;
        printf("Error - Position 0 5 should be on map\n");
    }
    destroy_position(&pos);

    pos = create_position(10, 5);
    if (is_position_on_map(pos)) {
        ++nb_error;
        printf("Error - Position 10 5 should not be on map\n");
    }
    destroy_position(&pos);

    pos = create_position(4, 5);
    tSoldier colonel = create_soldier(create_colonel(), BLUE, 0);
    set_soldier_on_map(map, pos, colonel);
    if (!is_colonel(get_unit(get_soldier_square(get_square(map, 4, 5))))) {
        ++nb_error;
        printf("Error - This should be a colonel on square 4 5\n");
    }
    clear_square_on_map(map, pos);
    if (is_colonel(get_unit(get_soldier_square(get_square(map, 4, 5))))) {
        ++nb_error;
        printf("Error - This square 4:5 should be cleared\n");
    }

    destroy_map(&map);
    if (map) {
        ++nb_error;
        printf("Error - Map not destroyed\n");
    }

    destroy_position(&pos);
    destroy_soldier(&colonel);

    return nb_error;
}

int test_can_he_move(void) {
    int nb_error = 0;
    tMap map = create_map();
    //print_map(map);
    tSoldier general = create_soldier(create_general(), BLUE, 0);
    tPosition posGeneral = create_position(5, 3);
    if (set_soldier_on_map(map, posGeneral, general)) {
        printf("Error - Not possible to set soldier here\n");
        ++nb_error;
    }
    //print_map(map);
    set_ordonnee(posGeneral, 4);
    if (!set_soldier_on_map(map, posGeneral, general)) {
        printf("Error - Actually possible to set soldier here\n");
        ++nb_error;
    }
    //print_map(map);

    tPosition posToGoTo = create_position(5,5);

    if (!can_soldier_move_to_pos(map, general, posToGoTo)) {
        ++nb_error;
        printf("Error - He can move\n");
    }
    if (!set_soldier_on_map(map, posToGoTo, general)) {
        printf("Error - Actually possible to set soldier here\n");
        ++nb_error;
    }
    //print_map(map);

    tSoldier colonelRed = create_soldier(create_colonel(), RED, 0);
    tPosition posColonelRed = create_position(5, 4);
    tSoldier colonelBlue = create_soldier(create_colonel(), BLUE, 0);
    tPosition posColonelBlue = create_position(6, 5);

    set_soldier_on_map(map, posColonelRed, colonelRed);
    set_soldier_on_map(map, posColonelBlue, colonelBlue);

    if (!(can_soldier_move_to_pos(map, general, posColonelRed) == 2)) {
        ++nb_error;
        printf("Error - He can move -> Fight\n");
    }
    //print_map(map);
    if (can_soldier_move_to_pos(map, general, posColonelBlue)) {
        ++nb_error;
        printf("Error - He can't move -> Ally\n");
    }
    
    destroy_map(&map);

    destroy_position(&posToGoTo);
    destroy_position(&posGeneral);
    destroy_position(&posColonelBlue);
    destroy_position(&posColonelRed);

    destroy_soldier(&general);
    destroy_soldier(&colonelBlue);
    destroy_soldier(&colonelRed);

    return nb_error;
}

int test_move(void) {
    int nb_error = 0;

    tMap map = create_map();
    tSoldier marshall = create_soldier(create_marshall(),BLUE,0);

    tPosition posMarshall = create_position(2, 3);
    set_soldier_on_map(map, posMarshall, marshall);
    //print_map(map);

    tPosition posToGo = create_position(3, 3);
    if (!move_soldier_to_pos_2(map, marshall, posToGo)) {
        ++nb_error;
        printf("Error - marshall should have moved\n");
    }
    if (!are_pos_equals(get_position(marshall), posToGo)) {
        ++nb_error;
        printf("Error - Pos are supposed to be equals.\n");
    }
    //print_map(map);
    printf("\n");

    tSoldier colonel = create_soldier(create_colonel(),RED,0);
    tPosition posColonel = create_position(3, 4);
    set_soldier_on_map(map, posColonel, colonel);
    printf("--- Colonel set\n");
    //print_map(map);
    printf("\n");

    if (!move_soldier_to_pos_2(map, marshall, posColonel)) {
        ++nb_error;
        printf("Error - marshall should have moved and kill colonel.\n");
    }
    if (!are_pos_equals(get_position(marshall), posColonel)) {
        ++nb_error;
        printf("Error - Pos are supposed to be equals, marshall killed colonel.\n");
    }
    //print_map(map);
    printf("\n");

    tPosition posBeforeLake = create_position(4, 4);
    if (!move_soldier_to_pos_2(map, marshall, posBeforeLake)) {
        ++nb_error;
        printf("Error - marshall should have moved to pos before lake.\n");
    }
    if (!are_pos_equals(get_position(marshall), posBeforeLake)) {
        ++nb_error;
        printf("Error - Pos are supposed to be equals, marshall moved before lake.\n");
    }
    //print_map(map);
    printf("\n");

    tPosition posLake = create_position(4, 3);
    if (move_soldier_to_pos_2(map, marshall, posLake)) {
        ++nb_error;
        printf("Error - marshall should NOT have moved into lake.\n");
    }
    if (are_pos_equals(get_position(marshall), posLake)) {
        ++nb_error;
        printf("Error - Pos are NOT supposed to be equals, marshall cannot move on lake.\n");
    }
    //print_map(map);
    printf("\n");

    destroy_soldier(&marshall);
    destroy_soldier(&colonel);
    destroy_position(&posMarshall);
    destroy_position(&posColonel);
    destroy_position(&posBeforeLake);
    destroy_position(&posLake);
    destroy_position(&posToGo);
    destroy_map(&map);

    return nb_error;
}

/*
    --------------------------------------- STRATEGO TEST ---------------------------------------
*/
int test_stratego(void) {
    int nb_error = 0;

    // tPosition pos = get_user_pos();
    // if (!is_position_on_map(pos)) {
    //     ++nb_error;
    //     printf("Error - Uniquement des coordonnées correctes sont acceptées.\n");
    // }

    // tMap map = create_map();
    // tSoldier soldierToTarget = create_spy_soldier(BLUE, 0);
    // tPosition posToTarget = create_position(3, 4);

    // set_soldier_on_map(map, posToTarget, soldierToTarget);
    // print_map(map);

    // tSoldier soldierToMove = get_soldier_user(map, BLUE);
    // if (!soldierToMove) {
    //     ++nb_error;
    //     printf("Error - Un soldat doit être choisi.\n");
    // }

    // tPosition posToMove = create_position(4, 4);
    // if (!can_soldier_move_to_pos(map, soldierToMove, posToMove)) {
    //     ++nb_error;
    //     printf("Error - Soldier on (3, 4) can move to (4, 4).\n");
    // }
    // move_soldier_to_pos_2(map, soldierToMove, posToMove);
    // print_map(map);

    // printf("Let's play a turn.\n");
    // tBoard board = create_board(map, create_army(BLUE), create_army(RED));
    // play_a_turn(board);
    // print_map(map);

    // destroy_soldier(&soldierToTarget);
    // destroy_position(&posToTarget);
    // destroy_position(&pos);
    // destroy_map(&map);

    return nb_error;
}

int test_turn_with_fight(void) {
    int nb_error = 0;

    tBoard board = create_board(create_map(), create_army(BLUE), create_army(RED));

    set_whole_blue_army_on_map(get_board_map(board), get_blue_army(board));
    set_whole_red_army_on_map(get_board_map(board), get_red_army(board));

    enum side_color side_to_play = RED;
    print_hidden_map(get_board_map(board), side_to_play);

    for (int i = 0 ; i < 1 ; ++i) {
        play_a_turn(board);
        print_hidden_map(get_board_map(board), get_playing_side(board));
        side_to_play = (side_to_play == BLUE ? RED : BLUE);
    }

    destroy_board(&board);
    return nb_error;
}

/*   Tests launcher - main   */
int main(void) {
    int is_error = 0;
    // ---------------- unit creation ----------------
    printf("--- Unit Creation ---\n");
    // are units the units they pretend to be
    is_error += test_creators_comparators();
    if (is_error == 0) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }
    is_error = 0;
    // ---------------- fights ----------------
    printf("--- Fights tests ---\n");
    // normal fights
    is_error += test_fight_marshall_general();
    is_error += test_fight_scout_scout();
    is_error += test_fight_colonel_marshall();
    
    // bombs
    is_error += test_fight_marshall_bomb();
    is_error += test_fight_miner_bomb();

    // spies
    is_error += test_fight_spy_marshall();
    is_error += test_fight_spy_bomb();
    is_error += test_fight_spy_scout();
    is_error += test_fight_marshall_spy();

    // flags
    is_error += test_fight_miner_flag();
    is_error += test_fight_scout_flag();

    if (is_error == 0) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }
    is_error = 0;

    // ---------------- soldier tests ----------------
    printf("--- Soldier Test ---\n");
    is_error += test_creation_destruction_soldier();

    if (!is_error) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }
    is_error = 0;

    // ---------------- army creation ----------------
    printf("--- Army Test ---\n");
    is_error += test_creation_army();
    if (!is_error) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }

    // ---------------- position test ----------------
    printf("--- Position Test --- \n");
    is_error += test_position();
    if (!is_error) {
        printf("Ok Position\n");
    } else {
        printf("%d errors. Position\n", is_error);
    }

    is_error += test_distance();
    if (!is_error) {
        printf("Ok Distance\n");
    } else {
        printf("%d errors. Distance\n", is_error);
    }

    // ---------------- square test ----------------
    printf("--- Square Test ---\n");
    is_error += test_square();
    if (!is_error) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }
    is_error = 0;

    // ---------------- map test ----------------
    printf("--- Map Test ---\n");
    is_error += test_map();
    if (!is_error) {
        printf("Ok Map\n");
    } else {
        printf("%d errors. Map\n", is_error);
    }
    is_error = 0;
    printf("\n");
    is_error += test_can_he_move();
    if (!is_error) {
        printf("Ok Can Move\n");
    } else {
        printf("%d errors. Can Move\n", is_error);
    }
    is_error = 0;

    printf("\n");
    is_error += test_move();
    if (!is_error) {
        printf("Ok Move\n");
    } else {
        printf("%d errors. Move\n", is_error);
    }

    // ---------------- stratego test ----------------
    printf("--- Stratego Test ---\n");
    // is_error += test_stratego();
    // if (!is_error) {
    //     printf("Ok Stratego\n");
    // } else {
    //     printf("%d errors. Stratego\n", is_error);
    // }
    // is_error = 0;
    // printf("\n");

    is_error += test_turn_with_fight();
    if (!is_error) {
        printf("Ok Stratego fight\n");
    } else {
        printf("%d errors. Stratego fight\n", is_error);
    }
    is_error = 0;
    printf("\n");

    return 0;
}