#include <stdio.h>
#include <stdlib.h>
#include "unite.h"
#include "army.h"
#include "map.h"
#include "position.h"
#include "square.h"

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
    if (!is_captain(create_captain())) {
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

    tSoldier *army = create_army(BLUE);

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

    for (int i = 0 ; i < SIZE_ARMY ; ++i) {
        if (!army[i]) {
            printf("\tError - Not %d soldiers in army.\n", SIZE_ARMY);
            ++nb_error;
        } else {
            if (is_flag(get_unit(army[i]))) {
                --nb_flag;
            }
            if (is_bomb(get_unit(army[i]))) {
                --nb_bomb;
            }
            if (is_marshall(get_unit(army[i]))) {
                --nb_marshall;
            }
            if (is_general(get_unit(army[i]))) {
                --nb_general;
            }
            if (is_spy(get_unit(army[i]))) {
                --nb_spy;
            }
            if (is_colonel(get_unit(army[i]))) {
                --nb_colonel;
            }
            if (is_major(get_unit(army[i]))) {
                --nb_major;
            }
            if (is_captain(get_unit(army[i]))) {
                --nb_captain;
            }
            if (is_lieutenant(get_unit(army[i]))) {
                --nb_lieutenant;
            }
            if (is_sergeant(get_unit(army[i]))) {
                --nb_sergeant;
            }
            if (is_miner(get_unit(army[i]))) {
                --nb_miner;
            }
            if (is_scout(get_unit(army[i]))) {
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
            if (!is_square_empty(squares[i][j])) {
                ++nb_error;
                printf("Error - Square should be empty (map creation)\n");
            }
        }
    }
    
    if (squares[10][9] != get_square(map, 10, 9)) {
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
    tSoldier soldat = create_soldier(create_colonel(), BLUE, 0);
    set_soldier_on_map(map, pos, soldat);
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
    destroy_soldier(&soldat);

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
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }

    is_error += test_distance();
    if (!is_error) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }

    // ---------------- square test ----------------
    printf("--- Square Test ---\n");
    is_error += test_square();
    if (!is_error) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }

    // ---------------- map test ----------------
    printf("--- Map Test ---\n");
    is_error += test_map();
    if (!is_error) {
        printf("Ok\n");
    } else {
        printf("%d errors.\n", is_error);
    }

    return 0;
}