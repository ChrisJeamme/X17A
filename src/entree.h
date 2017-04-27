#ifndef _ENTREE_H_
#define _ENTREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "decor.h"
#include "boule.h"

void GererClavier(unsigned char touche, int x, int y);
void GestionSpecial(int key, int x, int y);
void GererClavierMenu(unsigned char touche, int x, int y);

#endif