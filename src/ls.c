#include <stdio.h>
#include <stdlib.h>

#include "../include/noeud.h"

int ls(noeud *courant) {
    if (courant == NULL) {
        return 1;
    }
    
    liste_noeud *actuel = courant->fils;
    while (actuel != NULL) {
        print_noeud(actuel->no, actuel->no->nom);
        actuel = actuel->succ;
    }

    return 0;
}
