#define VIDE 0
#define PLEIN 1
#define RIEN 2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "fonctions.h"
#include "karbre.h"


#define EXTERIEUR 0
#define INTERSECTION 1
#define INTERIEUR 2

int position_cube_boule(Pointf centre_boule, int rayon_boule, Pointf p1, Pointf p2);
karbre boule2arbre(Pointf centre_boule, int rayon_boule, Pointf p1, Pointf p2);
karbre boule2karbre(Pointf centre_boule, int rayon_boule, Pointf p1, Pointf p2, float subdivision);
karbre intersection(karbre a1, karbre a2);
float distancefi(Pointf a, Point b);
float distancei(Point a, Point b);
float distancef(Pointf a, Pointf b);
void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2);
void affiche_boule(karbre arbre, Pointf p1, Pointf p2);
void dessiner_maison();