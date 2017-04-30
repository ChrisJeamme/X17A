#ifndef _JEU_H_
#define _JEU_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "decor.h"
#include "karbre.h"
#include "boule.h"
#include "entree.h"
#include "gui.h"
#include "menu.h"

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50 
#define SENS_MONTRE 1
#define SENS_INVERSE -1
#define LARGEUR_ELEMENT_DECOR 50
#define LIMITE_MAP 450

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

