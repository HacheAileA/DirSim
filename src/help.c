#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

int help() {
    printf(GRAS "\nCommandes disponibles :\n\n" RESET);
    printf(GRAS "  cd <nom>" RESET "             - Change de répertoire (.. pour remonter)\n");
    printf(GRAS "  cp <src> <dst>" RESET "       - Copie un fichier ou répertoire\n");
    printf(GRAS "  find <option> <nom>" RESET "  - Recherche un fichier dans l'arborescence\n");
    printf(GRAS "       -d" RESET " : Seulement les répertoires\n");
    printf(GRAS "       -f" RESET " : Seulement les fichiers\n");
    printf(GRAS "  help" RESET "                 - Affiche cette aide\n");
    printf(GRAS "  ls <chemin>" RESET "          - Liste le contenu du répertoire courant\n");
    printf(GRAS "  mkdir <nom>" RESET "          - Créé un répertoire\n");
    printf(GRAS "  mv <src> <dst>" RESET "       - Déplace ou renomme un fichier\n");
    printf(GRAS "  print" RESET "                - Affiche l'arborescence complète\n");
    printf(GRAS "  pwd" RESET "                  - Affiche le chemin courant\n");
    printf(GRAS "  q" RESET "                    - Quitte le programme\n");
    printf(GRAS "  rm <nom>" RESET "             - Supprime un fichier ou répertoire\n");
    printf(GRAS "  touch <nom>" RESET "          - Créé un fichier\n");
    
    return 0;
}
