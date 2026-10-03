#include <stdio.h>
#include "unite.h"
#include "army.h"
#include "map.h"

/*
    UNIT TEST
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
    ARMY TEST
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
    if (!(get_abcisse(get_position(soldier)) == 50)) {
        printf("\tError - Soldier abcisse is not 50 (=>%d)\n", get_abcisse(get_position(soldier)));
        ++nb_error;
    }
    if (!(get_ordonnee(get_position(soldier)) == 50)) {
        printf("\tError - Soldier ordonnee is not 50 (=>%d)\n", get_ordonnee(get_position(soldier)));
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



    return 0;
}