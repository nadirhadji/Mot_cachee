# TP1: Mot Cachée"

## Description :bookmark_tabs: ##

Ce travail est réalisée dans le cardre du cours INF3135 - Construction et maintenance de logiciel 
donnée a l'UQAM par Mr. Serge Dogny. 

Le but de ce TP est d'implementer un programme nommée ** Mot cachée **. Concretement, le programme recoit
en entrée un fichier conteant une matrice de lettres (12X12) suivi d'un espace puis une liste de mots a trouver
sur cette matrice. 

Le programme constitue un mot dit mot cachée avec les lettres n'appartenant a aucun mot sur la matrice.

## Auteur :pencil2:

Nadir Hadji (HADN08069703)

## Fonctionnement :wrench: ##

Il est préferable d'éxecuter ce projet dans un environnement Unix (Linux ou MacOS :heavy_check_mark:).
Des alternatives existe tout de meme sur Windows. Vous pouvez utiliser une machine virtuel, l'application Ubuntu ou plus simplement git bash.

Faire fonctionner ce projet en 3 étapes :

0. Telechargement (wget requis)
1. Compilation (GCC requis)
2. Execution

### Télechargement ###
Pour télecharger le projet taper les commandes suivantes :

```sh
$ wget https://gitlab.info.uqam.ca/hadji.nadir/inf3135-hiv2022-tp2
$ cd ./h22-inf3135-tp1
```

Vous vous trouverez dans le repertoire du projet.

### Compilation ###
Pour compiler le projet taper le commande : 

```sh
$ make
```

Ci vous n'avez par le programme GCC installer sur votre machine taper : 

```sh
$ sudo apt-get install gcc
```

### Execution ###

Pour afficher le manuel d'utilisation du projet taper la commande suivante apres la compilation:

```sh
$ ./motcache
```

Vous pouvez ecrire vos entrée en parametres comme suit :

```sh
$ ./motcache tests_folder/text.txt
```

## Tests :hammer: ##

Pour executer les testes automatiques, il est imperatif d'installer Bats sur ca machine. Pour cela ci ce n'est pas deja fait, vous pouvez lancer la commande : 

```sh
$ sudo apt-get install bats
```

Pour lancer les testes , lancer l'une des deux commandes suivantes : 

```sh
$ make test
```

```sh
$ bats check.bats --tap
```

Tout les testes sont en status 'ok' sauf le #8.


## Dépendances :books: ##

Les dépendances de projets sont : 

* GCC
* [Bats] (https://github.com/bats-core/bats-core)
* string.h (librairie standard)
* ctype.h (libraire standard)

