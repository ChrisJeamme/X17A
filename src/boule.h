#define VIDE 0
#define PLEIN 1
#define RIEN 2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "karbre.h"
#include "decor.h"

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
//Position de l'observateur
float ox;
float oy;
float oz;

int intersection_plan_boule(int x1, int y1, int z1, int x2, int y2, int z2);

int intersection_boule_plateforme();

void maj_vecteur_vitesse();

void maj_observateur();

void maj_position_boule();

void afficher_vecteurs();