#ifndef _ENTREE_H_
#define _ENTREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "boule.h"
#include "decor.h"


/*Pour tourner à droite*/
void droite();

/*Pour tourner à gauche*/
void gauche();

/*Pour accélerer*/
void accelere();

/*Pour ralentir*/
void decelere();

/*Fonctions qui gère les touches flechées*/
void GererClavier(unsigned char touche, int x, int y);

/*Gestion des touches normales*/
void GestionSpecial(int key, int x, int y);

/*Gère le menu*/
void GererClavierMenu(unsigned char touche, int x, int y);

#endif