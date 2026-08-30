#include <fnmatch.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/noeud.h"

char *BoolToString(bool b) {
    return (b) ? "-d" : "-f";
}

void find(noeud *courant, char *option, char *nom_cherche, char *chemin_actuel) {
    if (courant != &racine) {
        if (fnmatch(nom_cherche, courant->nom, 0) == 0 || fnmatch("", nom_cherche, 0) == 0) {
            if (fnmatch("", option, 0) == 0 || fnmatch(option, BoolToString(courant->est_dossier), 0) == 0) {
                print_noeud(courant, chemin_actuel);
            }
        }
    }

    liste_noeud *fils = courant->fils;
    while (fils != NULL) {
        char nouveau_chemin[1024];
        
        if (strcmp(chemin_actuel, "/") == 0)
            snprintf(nouveau_chemin, 1024, "/%s", fils->no->nom);
        else
            snprintf(nouveau_chemin, 1024, "%s/%s", chemin_actuel, fils->no->nom);
        
        find(fils->no, option, nom_cherche, nouveau_chemin);
        fils = fils->succ;
    }
}