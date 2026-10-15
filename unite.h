#ifndef UNITE_H
#define UNITE_H

typedef struct sUnite *tUnite;

// print
char *get_unit_abreviation(tUnite unit);

void get_all_abreviations(void);

/*
    --------------------------- Unit creation ---------------------------
*/
/*
    Unit strengh :
        flag : 0
        bomb : 100
        marshall : 10
        general : 9
        colonel : 8
        major : 7
        captain : 6
        lieutenant : 5
        sergeant : 4
        scout : 3
        miner : 2
        spy 1
*/
tUnite create_flag(void);
tUnite create_bomb(void);
tUnite create_marshall(void);
tUnite create_general(void);
tUnite create_colonel(void);
tUnite create_major(void);
tUnite create_captain(void);
tUnite create_lieutenant(void);
tUnite create_sergeant(void);
tUnite create_scout(void);
tUnite create_miner(void);
tUnite create_spy(void);

// Destroyer
void destroy_unit(tUnite *unit);

tUnite copy_unit(tUnite unit);

/*
    --------------------------- Getters ---------------------------
*/
char *get_name(tUnite unit);

unsigned int get_strengh(tUnite unit);

unsigned int get_movement(tUnite unit);

// comparators
int is_spy(tUnite unit);
int is_scout(tUnite unit);
int is_miner(tUnite unit);
int is_sergeant(tUnite unit);
int is_lieutenant(tUnite unit);
int is_captain(tUnite unit);
int is_major(tUnite unit);
int is_colonel(tUnite unit);
int is_general(tUnite unit);
int is_marshall(tUnite unit);
int is_bomb(tUnite unit);
int is_flag(tUnite unit);

int are_units_equal(tUnite unit1, tUnite unit2);

int can_unit_move(tUnite unit);


/*
    --------------------------- Fight ---------------------------
*/
// returns 1, 2 or 3 (being unit 1 and unit2 in order. 3 if both units are killed)
int who_wins(tUnite unit1, tUnite unit2);


#endif