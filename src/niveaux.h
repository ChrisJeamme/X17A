#ifndef _NIVEAUX_H_
#define _NIVEAUX_H_


#include "jeu.h"
#include "boule.h"
#include "decor.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef WIN32
    #include <sys/types.h>
#endif

typedef struct dirent dirent;

void importer_niveaux();
void fixer_nombre_niveaux();
void initialiser_tableaux_niveaux();
void importer_niveau(char* nom_fichier, int numero_niveau);
void afficher_niveaux();

#endif