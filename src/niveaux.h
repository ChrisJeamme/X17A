#ifndef _NIVEAUX_H_
#define _NIVEAUX_H_


#include "boule.h"
#include "jeu.h"
#include "decor.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef WIN32
    #include <sys/types.h>
#endif

typedef struct dirent dirent;

/*Importe les niveaux contenu dans le dossier ./level/*/
void importer_niveaux();
/*Compte le nombre de niveaux dans le dossier*/
void fixer_nombre_niveaux();
/*Alloue la mémoire aux tableaux qui contiendront tous les niveaux*/
void initialiser_tableaux_niveaux();
/*Importe les donnés d'un fichier niveau, avec son nom de fichier*/
void importer_niveau(char* nom_fichier, int numero_niveau);
/*Affiche quelques données des niveaux stockés (manque obstacle + sauts)*/
void afficher_niveaux();

#endif