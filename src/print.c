#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/noeud.h"

int printTout(int decalage, noeud *noeud) {
    for (int i = 0; i < decalage; i++) {
        printf(" ");
    }

    printf("%s ", (noeud == &racine || noeud->nom[0] == '\0') ? "/" : noeud->nom);

    if (noeud->est_dossier) {
        printf("(D) ");
    } else {
        printf("(F) ");
    }

    printf("[père : %s]\n", (noeud->pere == &racine || noeud->pere->nom[0] == '\0') ? "/" : noeud->pere->nom);

    liste_noeud *actuel = noeud->fils;
    while (actuel != NULL) {
        printTout(decalage + 2, actuel->no);
        actuel = actuel->succ;
    }

    return 0;
}

int print() {
    printTout(0, &racine);

    return 0;
}