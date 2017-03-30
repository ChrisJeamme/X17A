#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

void dessiner_plan1(int x1, int y1, int z1, int x2, int y2, int z2)
{
    glBegin(GL_QUADS);
        //Face dessous
        glVertex3f(x1, y1, z1);    
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);

        //Face dessus
        glVertex3f(x1, y2, z1);    
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        //Face devant
        glVertex3f(x1, y1, z1);    
        glVertex3f(x2, y1, z1);  
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);

        //Face derrière
        glVertex3f(x1, y1, z2);    
        glVertex3f(x2, y1, z2);  
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        //Face gauche
        glVertex3f(x1, y1, z1);    
        glVertex3f(x1, y2, z1);  
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y1, z2);    

        //Face droite
        glVertex3f(x2, y1, z1);    
        glVertex3f(x2, y2, z1);  
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);  
    glEnd();
}



//Tracage de la grille des points
void trace_grille(int n)
{
    glColor3f(1.0,1.0,1.0); //Blanc
    
    //Afficher X et Y sur le repère
    afficherText(10,0,0,1,1,"X");
    afficherText(0,10,0,1,1,"Y");
    afficherText(-10,0,0,1,1,"X");
    afficherText(0,-10,0,1,1,"Y");
    // glBegin(GL_LINES);
    // for(int i=-TAILLE; i<=TAILLE; i+=n)
    // {
    //     glVertex2i(-TAILLE, i);
    //     glVertex2i(TAILLE, i);
    //     glVertex2i(i, TAILLE);
    //     glVertex2i(i, -TAILLE);
        
    // }
    // glEnd();

    glColor3f(1.0,0.0,0.0); //Rouge

    glBegin(GL_LINES);  //X
        glVertex3i(-TAILLE,0,0);
        glVertex3i(TAILLE,0,0);
    glEnd();

    glBegin(GL_LINES); //Y
        glVertex3i(0,-TAILLE,0);
        glVertex3i(0,TAILLE,0);
    glEnd();

    glBegin(GL_LINES); //Z
        glVertex3i(0,0,-TAILLE);
        glVertex3i(0,0,TAILLE);
    glEnd();

    glFlush();

    glColor3f(1.0,1.0,1.0); //Blanc
}

void afficherText(float x, float y, int r, int g, int b, const char *texte) 
{
	int i, j = strlen(texte);
	glColor3f(r,g,b);
	glRasterPos2f(x,y);
	for(i=0; i<j; i++)
    {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, texte[i] );
	}
}