#ifndef _BOULE_H_
#define _BOULE_H_


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "karbre.h"
#include "decor.h"

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


int collison_boule_plateforme();

void maj_vecteur_vitesse();

void maj_observateur();

void maj_position_boule();

void afficher_vecteurs();

#endif