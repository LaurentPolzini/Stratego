#include <stdio.h>
#include <stdlib.h>
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

// ------------------------------------ Destroyers ------------------------------------
void destroy_position(tPosition *pos) {
    if (pos && *pos) {
        free(*pos);
        *pos = NULL;
    }
}
