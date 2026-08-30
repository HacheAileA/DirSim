#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

int mkdir(char *nom, noeud *courant) {
    if (!est_nom_valide(nom)) {
        return 1;
    }

    if (checkDuplicates(nom, courant)) {
        return 1;
    }

    noeud *dossier = malloc(sizeof(noeud));
    if (dossier == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de dossier dans mkdir (mkdir.c)\n" RESET);
        return 2;
    }
    dossier->est_dossier = true;
    strncpy(dossier->nom, nom, 99);
    dossier->pere = courant;
    dossier->racine = &racine;
    dossier->fils = NULL;

    liste_noeud *suivant = malloc(sizeof(liste_noeud));
    if (suivant == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de suivant dans mkdir (mkdir.c)\n" RESET);
        return 2;
    }
    suivant->no = dossier;
    suivant->succ = NULL;

    liste_noeud *actuel = courant->fils;
    if (actuel == NULL) {
        courant->fils = suivant;
    } else {
        while (actuel->succ != NULL) {
            actuel = actuel->succ;
        }
        actuel->succ = suivant;
    }

    return 0;
}
