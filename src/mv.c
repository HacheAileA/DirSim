#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"



int mv(char *chem1, char *chem2, noeud *courant) {

    noeud *source = chem_to_noeud(chem1, courant);
    if (source == NULL) {
        printf(ROUGE "ERREUR : '%s' n'existe pas\n" RESET, chem1);
        return 1;
    }

    char chem2_copie[100];
    strncpy(chem2_copie, chem2, 100 - 1);

    char *nouveau_nom;
    noeud *dest_parent;

    noeud *dest = chem_to_noeud(chem2, courant);
    if (dest != NULL && dest->est_dossier) {
        dest_parent = dest;
        nouveau_nom = source->nom;
    } else {
        nouveau_nom = strrchr(chem2_copie, '/');
        if (nouveau_nom == NULL) {
            nouveau_nom = chem2_copie;
            dest_parent = courant;
        } else if (nouveau_nom == chem2_copie) {
            nouveau_nom++;
            dest_parent = &racine;
        } else {
            *nouveau_nom = '\0';
            nouveau_nom++;
            dest_parent = chem_to_noeud(chem2_copie, courant);
        }
    }
    

    if (dest_parent == NULL || !dest_parent->est_dossier) {
        printf(ROUGE "ERREUR : dossier destination invalide\n" RESET);
        return 1;
    } else if (est_ancetre(source, dest_parent)) {
        printf(ROUGE "ERREUR : la destination est dans le sous-arbre source\n" RESET);
        return 1;
    } else if (est_ancetre(source, courant)) {
        printf(ROUGE "ERREUR : impossible de deplacer un parent du dossier courant\n" RESET);
        return 1;
    }

    liste_noeud *tmp = dest_parent->fils;
    while (tmp != NULL) {
        if (strcmp(tmp->no->nom, nouveau_nom) == 0) {
            printf(ROUGE "ERREUR : '%s' existe deja dans la destination\n" RESET, nouveau_nom);
            return 1;
        }
        tmp = tmp->succ;
    }


    liste_noeud *prec = NULL;
    liste_noeud *cur = source->pere->fils;
    while (cur->no != source) {
        prec = cur;
        cur = cur->succ;
    }
    if (prec == NULL) {
        source->pere->fils = cur->succ;
    } else {
        prec->succ = cur->succ;
    }
    free(cur);

    strncpy(source->nom, nouveau_nom, 99);
    source->pere = dest_parent;

    liste_noeud *maillon = malloc(sizeof(liste_noeud));
    if (maillon == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de maillon dans mv (mv.c)\n" RESET);
        return 2;
    }
    maillon->no = source;
    maillon->succ = dest_parent->fils;
    dest_parent->fils = maillon;

    return 0;
}