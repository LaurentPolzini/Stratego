#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "position.h"

struct sPosition {
    unsigned int abcisse;
    unsigned int ordonnee;
};

// ------------------------------------ Creators ------------------------------------
tPosition create_position(unsigned int abciss, unsigned int ordonne) {
    tPosition pos = malloc(sizeof(struct sPosition));
    pos->abcisse = abciss;
    pos->ordonnee = ordonne;
    return pos;
}

// ------------------------------------ Getters ------------------------------------
unsigned int get_abcisse(tPosition pos) {
    if (!pos) return OUT_OF_POS;
    return pos->abcisse;
}
unsigned int get_ordonnee(tPosition pos) {
    if (!pos) return OUT_OF_POS;
    return pos->ordonnee;
}

// Get distance between two aligned (line or column) squares
unsigned int get_distance(tPosition posFrom, tPosition posTo) {
    if (!(posFrom && posTo)) {
        return UINT32_MAX;
    }
    unsigned int abcisse_posFrom = get_abcisse(posFrom);
    unsigned int ordonnee_posFrom = get_ordonnee(posFrom);

    unsigned int abcisse_posTo = get_abcisse(posTo);
    unsigned int ordonnee_posTo = get_ordonnee(posTo);

    if (!((abcisse_posFrom == abcisse_posTo) || (ordonnee_posFrom == ordonnee_posTo))) {
        // not aligned squares
        return UINT32_MAX;
    }
    return abs((int) (abcisse_posFrom - abcisse_posTo) + (int) (ordonnee_posFrom - ordonnee_posTo));
}

// ------------------------------------ Setters ------------------------------------
// Set column of a pos
void set_abcisse(tPosition pos, unsigned int abciss) {
    if (!pos) return;
    pos->abcisse = abciss;
}
// Set line of a pos
void set_ordonnee(tPosition pos, unsigned int ordonne) {
    if (!pos) return;
    pos->ordonnee = ordonne;    
}

// ------------------------------------ Destroyers ------------------------------------
void destroy_position(tPosition *pos) {
    if (pos && *pos) {
        free(*pos);
        *pos = NULL;
    }
}
