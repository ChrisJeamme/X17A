#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "volume.h"

#define EXTERIEUR 0
#define INTERSECTION 1
#define INTERIEUR 2


void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2)
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



void dessiner_boule(float rayon, float x, float y, float z)
{
    glColor3f(1,0,0);   //Rouge 
    glTranslatef(x, y, z);
    glutSolidSphere(rayon, 20, 20 );
    glTranslatef(-x, -y, -z);
    glColor3f(1,1,1);   //Blanc
}

//   glClearColor(0.0F,0.0F,0.0F,0.0F) ;
//   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT) ;
//   glPushMatrix() ;
//   glRotatef(anglex,1.0F,0.0F,0.0F) ;
//   glRotatef(angley,0.0F,1.0F,0.0F) ;
//   glRotatef(anglez,0.0F,0.0F,1.0F) ;
//   glTranslatef(0.5F,0.0F,0.0F) ;
//   GLfloat rouge[] = { 1.0,0.0,0.0,0.0 };
//   glMaterialfv(GL_FRONT,GL_DIFFUSE,rouge);
//   glutSolidCube(0.6) ;
//   glTranslatef(-1.0F,0.0F,0.0F) ;
//   GLfloat vert[] = { 0.0,1.0,0.0,0.0 };
//   glMaterialfv(GL_FRONT,GL_DIFFUSE,vert);
//   glutSolidSphere(0.4,50,50) ;
//   glPopMatrix() ;
//   glFlush() ;
//   glutSwapBuffers() ;