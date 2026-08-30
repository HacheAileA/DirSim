#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/macros.h"
#include "../include/noeud.h"

noeud racine = {
    .est_dossier = true,
    .nom = "",
    .pere = &racine,
    .racine = &racine,
    .fils = NULL
};

int clearNoeud(noeud *courant) {
    if (courant == NULL) {
        return 0;
    }

    liste_noeud *actuel = courant->fils;
    while (actuel != NULL) {
        liste_noeud *suivant = actuel->succ;
        clearNoeud(actuel->no);
        free(actuel->no);
        free(actuel);
        actuel = suivant;
    }
    courant->fils = NULL;

    return 0;
};

int checkDuplicates(char *nom, noeud *courant) {
    liste_noeud *noeud = courant->fils;
    while (noeud != NULL) {
        if (strcmp(noeud->no->nom, nom) == 0) {
            printf(ROUGE "ERREUR : LE NOEUD %s EXISTE DÉJÀ DANS %s!\n" RESET, nom, strlen(courant->nom) == 0 ? "/ " : courant->nom);
       
            return 1;
        }
        noeud = noeud->succ;
    }
    return 0;
}

int est_nom_valide(char *nom) {
    if (nom == NULL || strlen(nom) == 0 || strlen(nom) > 99) {
        fprintf(stderr, ROUGE "ERREUR : nom invalide (vide ou trop long)\n" RESET);
        return 0;
    }
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalnum(nom[i])) {
            fprintf(stderr, ROUGE "ERREUR : nom invalide (caractères non alphanumériques)\n" RESET);
            return 0;
        }
    }
    return 1;
}

noeud *chem_to_noeud(char *chem, noeud *courant) {
    if (!courant) {
        return NULL;
    } else if (chem == NULL || strlen(chem) == 0) {
        return courant;
    }

    noeud *res;
    if (chem[0] == '/') {
        res = &racine;
    } else {
        res = courant;
    }

    char copie[100];
    strncpy(copie, chem, 99);

    char *token = strtok(copie, "/");
    while (token != NULL) {
        if (strcmp(token, "..") == 0) {
            res = res->pere;
        } else {
            liste_noeud *actuel = res->fils;

            while (actuel != NULL) {
                if (strcmp(actuel->no->nom, token) == 0) {
                    res = actuel->no;
                    break;
                }
                actuel = actuel->succ;
            }

            if (actuel == NULL) {
                return NULL;
            }
        }

        token = strtok(NULL, "/");
    }

    return res;
}

void print_noeud(noeud *noeud, char *nom) {
    if (noeud->est_dossier) {
        printf(GRAS "%s/" RESET "\n", nom);
    } else {
        printf("%s\n", nom);
    }
}


int est_ancetre(noeud *ancetre, noeud *n) {
    noeud *tmp = n;
    while (tmp != tmp->pere) { 
        if (tmp == ancetre) return 1;
        tmp = tmp->pere;
    }
    return tmp == ancetre; 
}

int est_option(char *nom) {
    return  strcmp(nom, "-d") == 0 ||
            strcmp(nom, "-f") == 0;
}
