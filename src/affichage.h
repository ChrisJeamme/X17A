#include "GL/gl.h"
#include "GL/glut.h"
#include "point.h"
#include <string.h>

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50

//Prototypes
//Tracage de la grille des points
void trace_grille(int n);

void afficherText(float x, float y, int r, int g, int b, const char *texte);

void dessiner_plan(int x1, int y1, int z1, int x2, int y2, int z2);