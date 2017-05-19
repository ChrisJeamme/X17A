#ifndef _JEU_H_
#define _JEU_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "boule.h"
#include "decor.h"
#include "karbre.h"
#include "entree.h"
#include "menu.h"
#include "niveaux.h"

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50 
#define SENS_MONTRE 1
#define SENS_INVERSE -1
#define LARGEUR_ELEMENT_DECOR 50
#define LIMITE_MAP 450
#define TAILLE_SAVE 100
#define NOMBRE_MAX_PLATEFORMES 100
#define NOMBRE_MAX_DECOR 500

//Analyse & interprétation des arguments
void gestion_arguments(int argc, char** argv);
//Paramètres d'initalisation et des objets
void initGL();
//Initialise les vecteurs au début du jeu
void majVecteurs();
void Animer();
void Affichage();
/*Lance le menu*/
void lancement();
/*Appeler via le menu pour lancer le jeu*/
void lancementJeu();
/*Permet de charger les textures depuis les fichiers*/
void init_texture();
// Défini le niveau selon num_niveau
void definir_niveau();
// Permet de changer de niveau
void choix_niveau(int choix_niveau);
void verification_limites();
/*Passe au niveau supérieur*/
void niveau_superieur();
/*Libère la mémoire des objets*/
void liberer_delivrer();

/*Booléen pour savoir si on affiche les textures*/
int no_texture;

/*Numéro du niveau choisi*/
int num_niveau;

#endif

