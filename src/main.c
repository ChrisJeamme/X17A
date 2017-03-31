#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"
#include "karbre.h"
#include "matrice.h"
#include "volume.h"

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50 
#define SENS_MONTRE 1
#define SENS_INVERSE -1

//Angle de rotation de l'observateur
float angle = .0;

//Sert pour changer le sens de rotation de l'observateur
int sens_rotation = SENS_MONTRE;
//Pour changer d'exemple dans affichage
int exemple = 0;

//Rayon de la boule
int brayon = 2;
//Coordonnées du centre de la boule
float bx = 0;
float by = 2;
float bz = 0;
//Vecteur de direction de la boule
float dx = 0;
float dy = 0;
float dz = 0;


void transformer_polyone_actuel(Matrice m);
void animer();
void Affichage();
void gererClavier(unsigned char touche, int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("La boule magique");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Affichage);
    glutIdleFunc(animer);
    glutKeyboardFunc(gererClavier);

    glutMainLoop();
    return 0;
}

void Affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix() ;
    glLoadIdentity();
    
    glFrustum(-1,1,-1,1,1,100);
    bx+=dx;
    bz+=dz;

    gluLookAt(bx-dx*400, by+brayon*4, bz-dz*400, bx, by+brayon, bz+1, 0, 1, 0);
	//glRotatef(angle,0,0,1);

    
    afficherText(0,12,1,1,1,"Test Boule");
    // dessiner_maison();
    dessiner_plan(-30,0,-30,30,0,30);
    dessiner_boule(brayon,bx,by,bz);

    trace_grille(5);
    glutSwapBuffers();
}

void animer()
{
    angle += .0 * sens_rotation;
    if(angle > 360)
        angle = 0;
    glutPostRedisplay();
}

void gererClavier(unsigned char touche, int x, int y)
{
    printf(" Touche: %c    Souris : %d %d \n",touche,x,y);

    if(touche=='z') //En haut
        dz += 0.01;  
    if(touche=='q') //A gauche
        dx -= 0.01;
    if(touche=='s') //En bas
        dz -= 0.01;  
    if(touche=='d') //A droite
        dx += 0.01;

    if (touche ==27) //Touche Echap => ferme le programme
		exit(0);
}

// glColor3f(1.0,0.5,0.0); //Orange
// glColor3f(0.0,0.0,1.0); //Bleu
// glColor3f(1.0,0.0,1.0); //Violet
// glColor3f(1.0,1.0,0.0); //Jaune
// glColor3f(0.0,1.0,1.0); //Cyan
// glColor3f(0.0,1.0,0.0); //Vert
// glCOlor3d(0.5,1.0,0.5); //Vert clair
// glColor3d(0.8,0.1,0.1); //Rouge tuile
// glColor3d(0.9,0.8,0.6); //Mur 1
// glColor3d(0.9,0.8,0.5); //Mur 2