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


int intersection_plan_boule(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int x3 = x2;
    int y3 = y1;
    int z3 = z3;

    float ABx = x2 - x1;
    float ABy = y2 - y1;
    float ABz = z2 - z1;

    float ACx = x3 - x1;
    float ACy = y3 - y1;
    float ACz = z3 - z1;

    //Produit vectoriel pour avoir vecteur normal au plan (ABC): 
    float a = ABy*ACz - ABz*ACy;
    float b = ABz*ACx - ABx*ACz;
    float c = ABx*ACy - ABy*ACx;
    //float d = -(a*x1 + b*x2 + c*x3); //car (x1,x2,x3) appartient au plan

    float Abx = bx - x1; 
    float Aby = by - y1; 
    float Abz = bz - z1;

    float distance = abs((Abx*a + Aby*b + Abz*c)/sqrt(a*a + b*b + c*c));


    if (distance > brayon)
        return 0;
    if ((bx < x1 && bx < x2 )||( bx > x1 && bx > x2 )||( bz < z1 && bz < z2 )||( bz > z1 && bz > z2))
        return 0;
    else return 1;


}



void dessiner_boule(float rayon, float x, float y, float z)
{
    glColor3f(1,0,0);   //Rouge 
    glTranslatef(x, y, z);
    glutSolidSphere(rayon, 20, 20 );
    glTranslatef(-x, -y, -z);
    glColor3f(1,1,1);   //Blanc
}
