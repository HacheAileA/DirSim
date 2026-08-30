#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

int touch(char *nom, noeud *courant) {
    if (!est_nom_valide(nom)) {
        return 1;
    }

    if (checkDuplicates(nom, courant)) {
        return 1;
    }

    noeud *fichier = malloc(sizeof(noeud));
    if (fichier == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de fichier dans touch (touch.c)\n" RESET);
        return 2;
    }
    fichier->est_dossier = false;
    strncpy(fichier->nom, nom, 99);
    fichier->pere = courant;
    fichier->racine = &racine;
    fichier->fils = NULL;

    liste_noeud *suivant = malloc(sizeof(liste_noeud));
    if (suivant == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de suivant dans touch (touch.c)\n" RESET);
        return 2;
    }
    suivant->no = fichier;
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
