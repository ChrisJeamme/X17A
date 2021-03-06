#ifndef _DECOR_H_
#define _DECOR_H_

#include "GL/gl.h"
#include "GL/glut.h"
#include "../lib/SOIL/SOIL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define NOMBRE_MAX_PLATEFORMES 100
#define NOMBRE_MAX_SAUTS 100
#define NOMBRE_MAX_OBJETS 1000
#define NOMBRE_MAX_DECOR 500

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

typedef struct struct_couple_points
{
    point p1;
    point p2;
} couple_points;

typedef struct struct_objet
{
    point p1;
    point p2;
    couleur coul;
} objet;

typedef struct struct_element_decor
{
    point p1;
    point p2;
    point p3;
    point p4;
    couleur couleur_dessus;
    couleur couleur_cotes;
} element_decor;

//Les objets du niveau actuel

plateforme tab_plateformes[NOMBRE_MAX_PLATEFORMES];
int nb_plateformes;

objet tab_objets[NOMBRE_MAX_OBJETS];
int nb_objets;

plateforme tab_sauts[NOMBRE_MAX_SAUTS];
int nb_sauts;

element_decor tab_decor[NOMBRE_MAX_DECOR];
int nb_element_decor;

//Point depart
point start;
//Point d'arrivée
point goal;
char goal_orientation;

//Texture plateformes
GLuint tex_sol[3];
GLuint tex_skybox[6];
GLuint tex_portail[2];

//Gestion menus

int nSousmenu1, nSousmenu2, nMenuprincipal, nSousmenuChoixNiveau; // Numéros (identifiants) des menus

//Les niveaux chargé depuis les fichiers

int nombre_niveau;
point *point_depart_niveau;
point *point_arrivee_niveau;
char *orientation_arrive_niveau;
int *nombre_plateforme_niveau;
int *nombre_saut_niveau;
int *nombre_obstacle_niveau;
plateforme **plateforme_niveau;
plateforme **saut_niveau;
couple_points **obstacle_niveau;

//Prototypes

/*Permet de dessiner la boule avec un rayon donné et les coordonnées du centre*/
void dessiner_boule(float rayon, float x, float y, float z);

/*Ajoute une plate-forme grace a 4 points*/
void ajouter_plateforme(point p1, point p2, point p3, point p4);

/*Ajoute une plate-forme qui existe déjà au niveau*/
void ajouter_plateforme_charge(plateforme p);

/*Pareil pour plateforme de saut*/
void ajouter_saut_charge(plateforme p);

/*Ajoute une plateforme de saut*/
void ajouter_saut(point p1, point p2, point p3, point p4);

/*Ajoute un objet dans le monde*/
void ajouter_objet(point p1, point p2, char c);

/*Affiche les objets*/
void afficher_objets();

/*Ajoute un élément (pavé) au décor du dessous*/
void ajouter_element_decor(point p1, point p2, point p3, point p4);

/*Permet d'afficher une plateforme selon plusieurs couleurs*/
void afficher_la_plateforme(plateforme p, char couleur);

/*Permet d'afficher toutes les plateformes*/
void afficher_plateformes();

void afficher_decor();

void definir_decor(int largeur_element);

void afficher_cubemap();


/*Permet de charger une texture*/
void chargementTexture(GLuint* texture, char* chemin);

void chargerTextureCubemap(GLuint* texture, char *x_pos_file, char *x_neg_file, char *y_pos_file, char *y_neg_file, char *z_pos_file, char *z_neg_file);
/*Afficher un  texte d'une certaine couleur*/
void afficherText(float x, float y, int r, int g, int b, const char *texte);

void chargementTexture(GLuint* texture, char* chemin);

/*Permet de creer un point avec 3 coordonnées*/
point nouveau_point(int x, int y, int z);

void parallelepipede(int x1, int y1, int z1, int x2, int y2, int z2);

void portail(point p, char orientation);

void ajouter_pilier_portail(point p, char orientation);

void generer_objet_sur_plateforme(plateforme p);

/*maximum entre 3 entiers*/
int max(int x1, int x2, int x3);

/*minimum entre 3 entiers*/
int min(int x1, int x2, int x3);

float rand_0_1();

#endif