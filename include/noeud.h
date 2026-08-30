#include <stdbool.h>

struct noeud;
struct liste_noeud;

typedef struct noeud {
    bool est_dossier;
    char nom[100];
    struct noeud *pere;
    struct noeud *racine;
    struct liste_noeud *fils;
} noeud;

typedef struct liste_noeud {
    struct noeud *no;
    struct liste_noeud *succ;
} liste_noeud;

extern struct noeud racine;

// ==== Fonctions à implémenter ==== //

/* Affiche les fils du noeud 'courant' */
int ls(noeud *courant);

/* Déplace le pointeur vers le noeud 'courant' */
noeud *cd(char *chemin, noeud *courant);

/* Affiche le chemin absolu du noeud 'courant' */
int pwd(noeud *courant);

/* Créer un nouveau dossier 'nom' dans le noeud 'courant' */
int mkdir(char *nom, noeud *courant);

/* Créer un nouveau fichier 'nom' dans le noeud 'courant' */
int touch(char *nom, noeud *courant);

/* Supprimer le noeud représenté par le chemin 'chem' depuis 'courant' */
int rm(char *chem, noeud *courant);

/* Copie l'arborescence de 'source' dans 'cible' */
int cp(char *source, char *cible, noeud *courant);

/* Cherche dans l'arborescence le noeud représenté par le chemin 'nom_cherche' avec ou non une option */
void find(noeud *courant, char *option, char *nom_cherche, char *chemin_actuel);

/* Déplace l'arborescence de 'source' dans 'cible' */
int mv(char *source, char *cible, noeud *courant);

/* Affiche l'arbre complet */
int print();

/* Affiche la liste des commandes */
int help();



// ==== Fonctions personnelles ==== //

/* Supprime le noeud 'courant' en mémoire */
int clearNoeud(noeud *courant);

/* Vérifie qu'il n'y a pas de confilts de noms */
int checkDuplicates(char *nom, noeud *courant);

/* Vérifie que le nom est valide (alphanumérique, non vide, <= 99 chars) */
int est_nom_valide(char *nom);

/* Transforme un chemin en noeud à partir du noeud 'courant' */
noeud *chem_to_noeud(char *chem, noeud *courant);

/* Affiche le nom du noeud avec le "/" pour les dossiers */
void print_noeud(noeud *noeud, char *nom);

/* Vérifie si le noeud 'ancetre' est un ancetre du noeud 'n' (ou égal à lui) */
int est_ancetre(noeud *ancetre, noeud *n);

/* Vérifie si la chaîne est une option (-d, -f) */
int est_option(char *nom);