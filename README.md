## Table des matières

- [Structure](#structure)
- [Compilation](#compilation)
- [Exécution](#exécution)
- [Nettoyage](#nettoyage)
- [Tests](#tests)
- [Sources](#sources)

### Structure

Le projet est réparti en plusieurs dossiers et fichiers :
```
.
├── bin/            Fichier(s) exécutable(s) (créé par make)
├── build/          Fichiers intermédiaires (créé par make)
│   └── *.o
├── include/        Fichier(s) d'en-tête(s)
│   └── *.h
├── src/            Fichiers de code source
│   ├── main.c      Fichier principal, point d'entrée du programme
│   └── *.c         Fichier pour chaque fonction
├── test/           Fichiers de tests
│   ├── error/
│   └── other/
├── Makefile        Fichier de compilation
└── README.md
```

---

### Compilation
Créer les fichiers exécutables (bin) et .o (build) :
```bash
make all
```

---

### Exécution
L'ajout d'un fichier txt en paramètre n'est pas obligatoire.
- Avec Valgrind :
```bash
valgrind --leak-check=full ./bin/main ./test/other/test.txt
```

- Sans Valgrind :
```bash
./bin/main ./test/other/test.txt
```

---

### Nettoyage
Supprimer les fichiers exécutables (bin) et .o (build)
```bash
make clean
```

---

### Tests
Des fichiers de tests sont mis à disposition dans le dossier `test/` et sont divisés en 2 sous-dossiers :
- **error** : avec des erreurs pour montrer la robustesse du programme
- **other** : sans erreur pour tester toutes les fonctions

---

### Sources
- [Structure](https://www.lucavall.in/blog/how-to-structure-c-projects-my-experience-best-practices) du projet.

- [Optimiser](https://blog.stephane-robert.info/docs/developper/autres-outils/build/makefile/) le Makefile avec des variables automatiques.