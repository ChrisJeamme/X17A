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


void dessiner_maison()
{
    glBegin(GL_QUADS);

        float x = 5;
        float y = x;
        float z = x;

        glColor3f(1.0,0.5,0.0); //Orange
        //Face dessous
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);
        glVertex3f(x, 0, z);
        glVertex3f(0, 0, z);

        glColor3d(0.9,0.8,0.7); //Mur 1
        //Face devant
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);  
        glVertex3f(x, y, 0);
        glVertex3f(0, y, 0);

        glColor3d(0.9,0.8,0.5); //Mur 2
        //Face derrière
        glVertex3f(0, 0, z);    
        glVertex3f(x, 0, z);  
        glVertex3f(x, y, z);
        glVertex3f(0, y, z);

        glColor3d(0.9,0.8,0.7); //Mur 1
        //Face gauche
        glVertex3f(0, 0, 0);    
        glVertex3f(0, y, 0);  
        glVertex3f(0, y, z);
        glVertex3f(0, 0, z);    

        glColor3d(0.9,0.8,0.5); //Mur 2
        //Face droite
        glVertex3f(x, 0, 0);    
        glVertex3f(x, y, 0);  
        glVertex3f(x, y, z);
        glVertex3f(x, 0, z);  

    glEnd();

    glBegin(GL_QUADS);
        glColor3d(0.8,0,0); //Rouge un peu clair

        //Face dessus gauche
        glVertex3f(0, y, 0);   
        glVertex3f(0, y, z);
        glVertex3f(x/2, y+y/2, z);
        glVertex3f(x/2, y+y/2, 0);

        //Face dessus droite
        glVertex3f(x, y, 0);   
        glVertex3f(x, y, z);
        glVertex3f(x/2, y+y/2, z);
        glVertex3f(x/2, y+y/2, 0);

    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3d(0.8,0.1,0.1); //Rouge tuile
        //Face comblage avant
        glVertex3f(0, y, 0);   
        glVertex3f(x, y, 0);
        glVertex3f(x/2, y+y/2, 0);

        //Face comblage arrière
        glVertex3f(0, y, z);   
        glVertex3f(x, y, z);
        glVertex3f(x/2, y+y/2, z);
    glEnd();

    //On remet la couleur blanche
    glColor4f(1.0,1.0,1.0,1.0);
    
}

void dessiner_boule(int rayon, int x, int y, int z)
{
    glColor3f(1,0,0);   //Rouge 
    glTranslatef(x, y, z);
    glutSolidSphere(rayon, 20, 20 );
    glTranslatef(-x, -y, -z);
    glColor3f(1,1,1);   //Blanc
}