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

// ------------------------------------ Destroyers ------------------------------------
void destroy_position(tPosition *pos);

#endif
