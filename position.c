#include <stdio.h>
#include <stdlib.h>
#include "position.h"

struct sPosition {
    unsigned int abcisse;
    unsigned int ordonnee;
};

// ------------------------------------ Creators ------------------------------------
tPosition create_position(unsigned int i, unsigned int j) {
    tPosition pos = malloc(sizeof(struct sPosition));
    pos->abcisse = i;
    pos->ordonnee = j;
    return pos;
}

// ------------------------------------ Getters ------------------------------------
int get_abcisse(tPosition pos) {
    if (!pos) return -1;
    return pos->abcisse;
}
int get_ordonnee(tPosition pos) {
    if (!pos) return -1;
    return pos->ordonnee;
}

// ------------------------------------ Destroyers ------------------------------------
void destroy_position(tPosition *pos) {
    if (pos && *pos) {
        free(*pos);
        *pos = NULL;
    }
}
