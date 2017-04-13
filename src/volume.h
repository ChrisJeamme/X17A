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

//Rayon de la boule
int brayon;
//Coordonnées du centre de la boule
float bx;
float by;
float bz;
//Vecteur de vitesse de la boule
float vx;
float vy;
float vz;
//Vecteur d'accélération de la boule
float ax;
float ay;
float az;
//Vecteur de gravité de la boule
float gx;
float gy;
float gz;
//Angle de direction 
float angle;

void dessiner_boule(float rayon, float x, float y, float z);
void dessiner_maison();
void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2);
int intersection_plan_boule(int x1, int y1, int z1, int x2, int y2, int z2);