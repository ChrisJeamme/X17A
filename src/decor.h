#ifndef _DECOR_H_
#define _DECOR_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50

typedef struct struct_plateforme
{
    int x1; 
    int y1;
    int z1;
    int x2;
    int y2;
    int z2;
} plateforme;

plateforme tab_plateformes[100];
int nb_plateformes;

//Prototypes
void dessiner_boule(float rayon, float x, float y, float z);

void dessiner_plan(int x1, int y1, int z1, int x2, int y2, int z2);

void ajouter_plateforme(int x1, int y1, int z1, int x2, int y2, int z2);

void dessiner_plateformes();

void afficher_plateformes();

void trace_grille(int n);

void afficherText(float x, float y, int r, int g, int b, const char *texte);

void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2);

#endif