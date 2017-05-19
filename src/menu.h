#ifndef _MENU_H_
#define _MENU_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "boule.h"
#include "decor.h"
#include "jeu.h"

#define MENU_RESET 1
#define MENU_QUITTER 2

/*Affiche le menu (niveauxcipal)*/
void AffichageMenu();

/*Gère le menu clic droit*/
void gestionMenu();

/*Menu clic droit*/
void vRappelMenuPrincipal(int i);

/*Sous menu pour le choix de niveau*/
void vRappelSousmenuChoixNiveau(int i);



#endif