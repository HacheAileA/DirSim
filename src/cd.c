#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

noeud *cd(char *chemin, noeud *courant){
    if (!courant) {
        return NULL;
    } else if (!chemin) {
        return &racine;
    }

    noeud *cible = chem_to_noeud(chemin, courant);
    if (cible == NULL) {
        printf(ROUGE "ERREUR : LE CHEMIN EST INVALIDE!\n" RESET);
        return NULL;
    } else if (!cible->est_dossier) {
        printf(ROUGE "ERREUR : %s N'EST PAS UN DOSSIER\n" RESET, cible->nom);
        return NULL;
    }

    return cible;
}