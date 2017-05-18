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

void gestion_arguments(int argc, char** argv);
void initGL();
void majVecteurs();
void Animer();
void Affichage();
void lancement();
void lancementJeu();
void init_texture();
void definir_niveau();
void verification_limites();

int no_texture;

int num_niveau;

#endif

