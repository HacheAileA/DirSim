#include <stdio.h>
#include <stdlib.h>

#include "../include/noeud.h"

void afficherChemin(noeud *actuel) {
    if (actuel == &racine) {
        return;
    }
    afficherChemin(actuel->pere);
    printf("/%s", actuel->nom);
}

int pwd(noeud *courant) {
    if (courant == &racine) {
        printf("/\n");
        return 0;
    }
    afficherChemin(courant);
    printf("\n");
    return 0;
}