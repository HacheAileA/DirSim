#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

int rm(char *chem, noeud *courant) {
    noeud *cible = chem_to_noeud(chem, courant);
    if (cible == NULL) {
        printf(ROUGE "ERREUR : LE CHEMIN EST INVALIDE!\n" RESET);
        return 1;
    } else if (cible == &racine) {
        printf(ROUGE "ERREUR : IMPOSSIBLE DE SUPPRIMER LA RACINE!\n" RESET);
        return 1;
    }

    if (est_ancetre(cible, courant)) {
        printf(ROUGE "ERREUR : IMPOSSIBLE DE SUPPRIMER UN NOEUD PARENT!\n" RESET);
        return 1;
    }

    noeud *pere = cible->pere;
    liste_noeud *actuel = pere->fils;
    liste_noeud *prev = NULL;

    while (actuel != NULL) {
        if (actuel->no == cible) {
            if (prev == NULL) {
                pere->fils = actuel->succ;
            } else {
                prev->succ = actuel->succ;
            }
            free(actuel);
            break;
        }
        prev = actuel;
        actuel = actuel->succ;
    }

    clearNoeud(cible);
    free(cible);

    return 0;
}