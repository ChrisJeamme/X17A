#define VIDE 0
#define PLEIN 1
#define RIEN 2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "karbre.h"


#define EXTERIEUR 0
#define INTERSECTION 1
#define INTERIEUR 2

void dessiner_boule(int rayon, int x, int y, int z);
void dessiner_maison();
void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2);