#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct sPosition *tPosition;

#define OUT_OF_POS 50 // number over 10

// ------------------------------------ Creators ------------------------------------
tPosition create_position(unsigned int abciss, unsigned int ordonne);

// ------------------------------------ Getters ------------------------------------
// Get column of a pos
unsigned int get_ordonnee(tPosition pos);
// Get line of a pos
unsigned int get_abcisse(tPosition pos);

// Get distance between two aligned (line or column) squares
unsigned int get_distance(tPosition posFrom, tPosition posTo);

int are_pos_equals(tPosition pos1, tPosition pos2);

void copy_pos(tPosition posToCopy, tPosition whereToCopy);

// ------------------------------------ Setters ------------------------------------
// Set column of a pos
void set_abcisse(tPosition pos, unsigned int abciss);
// Set line of a pos
void set_ordonnee(tPosition pos, unsigned int ordonne);

// ------------------------------------ Destroyers ------------------------------------
void destroy_position(tPosition *pos);

#endif
