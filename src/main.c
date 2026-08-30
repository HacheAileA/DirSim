#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/macros.h"
#include "../include/noeud.h"

#define GESTION_ERREURS 1

FILE *open_file(const char *file) {
    FILE *res = NULL;

    if (file == NULL) {
        return NULL;
    }

    res = fopen(file, "r");
    if (res == NULL) {
        printf(ROUGE "ERREUR :  Impossible d'ouvrir le fichier %s\n" RESET, file);
        return NULL;
    }

    return res;
}

void close_file(FILE *file) {
    if (file != NULL) {
        fclose(file);
    }
}

int main(int argc, char *files[]) {
    FILE *file = open_file(files[1]);
    noeud *courant = &racine;
    int erreur = 0;

    char *cmd = malloc(MAX_LIGNE_SIZE * sizeof(char));
    if (cmd == NULL) {
        return 1;
    }

    FILE *mode = NULL;
    if (file == NULL) {
        printf(JAUNE MODE_TERMINAL RESET);
        printf(GRAS "\nBienvenue !" RESET " Tapez '" GRAS "help" RESET "' pour afficher la liste des commandes.\n");
        mode = stdin;
    } else {
        printf(JAUNE MODE_FICHIER RESET);
        mode = file;
    }

    while (true) {
        char *args[3] = {NULL, NULL, NULL};

        if (mode == stdin) {
            printf("\n~/%s $ ", courant->nom);
        }

        if (fgets(cmd, MAX_LIGNE_SIZE, mode) == NULL) {
            if (mode == file) {
                printf(GRAS "\nTOUTES LES INSTRUCTIONS DU FICHIER ONT ÉTÉ EXÉCUTÉ\n" RESET);
                printf(JAUNE MODE_TERMINAL RESET);
                mode = stdin;
                continue;
            } else {
                break;
            }
        }

        char *token = strtok(cmd, " \t\r\n");

        int i = 0;
        while (token != NULL && i < 3) {
            args[i] = token;
            token = strtok(NULL, " \t\r\n");
            i++;
        }

        if (args[0] != NULL) {
            if (strcmp(args[0], "help") == 0 && args[1] == NULL && args[2] == NULL) { // HELP
                help();
            } else if (strcmp(args[0], "mkdir") == 0 && args[1] != NULL && args[2] == NULL) { // MKDIR
                erreur = mkdir(args[1], courant);
            } else if (strcmp(args[0], "touch") == 0 && args[1] != NULL && args[2] == NULL) { // TOUCH
                erreur = touch(args[1], courant);
            } else if (strcmp(args[0], "ls") == 0 && args[2] == NULL) { // LS
                if (args[1] != NULL) {
                    erreur = ls(chem_to_noeud(args[1], courant));
                } else {
                    erreur = ls(courant);
                }
            } else if (strcmp(args[0], "print") == 0 && args[1] == NULL && args[2] == NULL) { // PRINT
                print();
            } else if (strcmp(args[0], "pwd") == 0 && args[1] == NULL && args[2] == NULL) { // PWD
                pwd(courant);
            } else if (strcmp(args[0], "cd") == 0 && args[2] == NULL) { // CD
                noeud *res = cd(args[1], courant);
                if (res != NULL) {
                    courant = res;
                } else {
                    erreur = 1;
                }
            } else if (strcmp(args[0], "rm") == 0 && args[1] != NULL && args[2] == NULL) { // RM
                erreur = rm(args[1], courant);
            } else if (strcmp(args[0], "cp") == 0 && args[1] != NULL && args[2] != NULL) { // CP
                erreur = cp(args[1], args[2], courant);
            } else if (strcmp(args[0], "find") == 0 && args[1] != NULL) { // FIND
                if (args[2] == NULL) {
                    if (est_option(args[1])) {
                        find(&racine, args[1], "", "/");
                    } else {
                        find(&racine, "", args[1], "/");
                    }
                } else {
                    find(&racine, args[1], args[2], "/");
                }
            } else if (strcmp(args[0], "mv") == 0 && args[1] != NULL && args[2] != NULL) { // MV
                erreur = mv(args[1], args[2], courant);
            }
        
            
            else if (strcmp(args[0], "q") == 0) { // QUIT
                break;
            } else {
                printf(ROUGE "Commande fausse\n" RESET);
            }

            if (!GESTION_ERREURS && erreur != 0) { // ERREUR
		break;
            }
        }
    }

    free(cmd);
    clearNoeud(&racine);
    close_file(file);

    return erreur;
}
