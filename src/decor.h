#ifndef _DECOR_H_
#define _DECOR_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include "../lib/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50

typedef struct struct_point
{
    int x;
    int y;
    int z;
} point;

typedef struct struct_couleur
{
    float r;
    float v;
    float b;
} couleur;

typedef struct struct_plateforme
{
    point p1;
    point p2;
    point p3;
    point p4;
} plateforme;

typedef struct struct_element_decor
{
    point p1;
    point p2;
    point p3;
    point p4;
    couleur couleur_dessus;
    couleur couleur_cotes;
} element_decor;

plateforme tab_plateformes[100];
int nb_plateformes;

element_decor tab_decor[500];
int nb_element_decor;

//Texture plateformes
GLuint tex_sol[2];

//Gestion menus

int nSousmenu1, nSousmenu2, nMenuprincipal; // Numéros (identifiants) des menus

//Prototypes

/*Permet de dessiner la boule avec un rayon donné et les coordonnées du centre*/
void dessiner_boule(float rayon, float x, float y, float z);

/*Ajoute une plate-forme grace a 4 points*/
void ajouter_plateforme(point p1, point p2, point p3, point p4);

/*Ajoute un élément (pavé) au décor du dessous*/
void ajouter_element_decor(point p1, point p2, point p3, point p4);


/*Permet d'afficher toutes les plateformes*/
void afficher_plateformes();

void afficher_decor();

void definir_decor();


/*Permet de charger une texture*/
void chargementTexture(GLuint* texture, char* chemin);

void trace_grille(int n);

void afficherText(float x, float y, int r, int g, int b, const char *texte);

void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2);

void chargementTexture(GLuint* texture, char* chemin);

/*Permet de creer un point avec 3 coordonnées*/
point nouveau_point(int x, int y, int z);



float rand_0_1();

#endif