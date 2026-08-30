#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

noeud *copie(noeud *source) {
    noeud *res = malloc(sizeof(noeud));
    if (res == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de res dans copie (cp.c)\n" RESET);
        return NULL;
    }

    res->est_dossier = source->est_dossier;
    strncpy(res->nom, source->nom, 99);
    res->pere = NULL;
    res->racine = &racine;
    res->fils = NULL;

    if (res->est_dossier) {
        liste_noeud *fils = source->fils;
        liste_noeud *fin = NULL;

        while (fils != NULL) {
            noeud *fils_1 = copie(fils->no);
            liste_noeud *fils_rest = malloc(sizeof(liste_noeud));
            if (fils_rest == NULL) {
                fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de fils_rest dans copie (cp.c)\n" RESET);
                return NULL;
            }

            fils_1->pere = res;

            fils_rest->no = fils_1;
            fils_rest->succ = NULL;

            if (res->fils == NULL) {
                res->fils = fils_rest;
            } else {
                fin->succ = fils_rest;
            }
            fin = fils_rest;

            fils = fils->succ;
        }
    }

    return res;
}

int cp(char *chem1, char *chem2, noeud *courant) {
    noeud *source = chem_to_noeud(chem1, courant);
    noeud *dest = chem_to_noeud(chem2, courant);

    if (source == NULL) {
        printf(ROUGE "ERREUR : LE CHEMIN '%s' EST INVALIDE!\n" RESET, chem1);
        return 1;
    } else if (source == &racine) {
        printf(ROUGE "ERREUR : LE NOEUD SOURCE EST LA RACINE!\n" RESET);
        return 1;
    }

    char chem2_copie[100];
    strncpy(chem2_copie, chem2, 100 - 1);

    char *nouveau_nom;
    noeud *dest_parent;
    
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
        printf(ROUGE "ERREUR : LE NOEUD SOURCE EST UN ANCETRE DU NOEUD %s!\n" RESET, dest_parent->nom);
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

    noeud *copie_source = copie(source);
    if (copie_source == NULL) {
        return 2;
    }
    copie_source->pere = dest_parent;
    strncpy(copie_source->nom, nouveau_nom, 99);

    liste_noeud *fils = malloc(sizeof(liste_noeud));
    if (fils == NULL) {
        fprintf(stderr, ROUGE "ERREUR : Echec d'allocation de fils dans cp (cp.c)\n" RESET);
        return 2;
    }
    fils->no = copie_source;
    fils->succ = NULL;

    if (dest_parent->fils == NULL) {
        dest_parent->fils = fils;
    } else {
        liste_noeud *actuel = dest_parent->fils;
        while (actuel->succ != NULL) {
            actuel = actuel->succ;
        }
        actuel->succ = fils;
    }

    return 0;
}
