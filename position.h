#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct sPosition *tPosition;

// ------------------------------------ Creators ------------------------------------
tPosition create_position(unsigned int i, unsigned int j);

// ------------------------------------ Getters ------------------------------------
// Get column of a pos
int get_ordonnee(tPosition pos);
// Get line of a pos
int get_abcisse(tPosition pos);

// ------------------------------------ Destroyers ------------------------------------
void destroy_position(tPosition *pos);

#endif
