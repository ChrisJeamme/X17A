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

void AffichageMenu();
void gestionMenu();

void vRappelSousMenu1(int i);
void vRappelMenuPrincipal(int i);
void vRappelSousmenuChoixNiveau(int i);



#endif