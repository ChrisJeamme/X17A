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
//Frottement
float fx;
float fz;
//Direction avant de s'arrêter
float dx;
float dz;

/*Calcule si la boule est en collision avec un des plan*/
int collison_boule_plateforme();


int collision_boule_face(int x1, int z1, int x2, int z2);

/*On modifie les vecteurs de la boule en fonction de la pente de la plate-forme*/
void ajouter_pente(int a, int b, int c);

/*Met a jour le vecteur vitesse*/
void maj_vecteur_vitesse();

/*Met a jour la postion de la boule*/
void maj_position_boule();

/*Met a jour la position de l'observateur*/
void maj_observateur();

/*maximum entre 3 entiers*/
int max(int x1, int x2, int x3);

/*minimum entre 3 entiers*/
int min(int x1, int x2, int x3);

/*Fonction de débeugage*/
void afficher_vecteurs();





#endif