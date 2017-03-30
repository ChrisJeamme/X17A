#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"
#include "affichage.h"
#include "karbre.h"
#include "volume.h"
#include <string.h>

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50 
#define SENS_MONTRE 1
#define SENS_INVERSE -1

//Angle de rotation de l'observateur
float angle = .0;
//Coordonnées de base de l'observateur
int px = 20;
int py = 10;
int pz = 10;
//Sert pour changer le sens de rotation de l'observateur
int sens_rotation = SENS_MONTRE;
//Pour changer d'exemple dans affichage
int exemple = 0;

void afficherText(float x, float y, int r, int g, int b, const char *string);
void transformer_polyone_actuel(Matrice m);
void animer();
void gererClavier(unsigned char touche, int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Projet X17A");
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,1,100);
    gluLookAt(px, py, pz, -px, -py, -pz, 0, 1, 0);
    glRotatef(angle, 0,1,0);

    //Afficher X et Y sur le repère
    afficherText(10,0,0,1,1,"X");
    afficherText(0,10,0,1,1,"Y");
    afficherText(-10,0,0,1,1,"X");
    afficherText(0,-10,0,1,1,"Y");
    
    //Création des 2 boules et de leur intersection
    Pointf centre = creer_pointf(0,0,0);
    Pointf centre2 = creer_pointf(5,0,0);
    Pointf p1 = creer_pointf(-50,-50,-50);
    Pointf p2 = creer_pointf(50,50,50);
    karbre test1 = boule2arbre(centre, 4, p1, p2);
    karbre test2 = boule2arbre(centre2, 5, p1, p2);
    karbre test3 = intersection(test1,test2);

    //Texte en haut à droite de la fenêtre
    afficherText(0,17,1,1,1,"Appuyez sur C pour continuer");
    afficherText(0,16,1,1,1,"Appuyez sur A pour changer de sens");

    //Selection de l'exemple (Touche C: voir gererClavier() )
    if(exemple==0)
    {
        afficherText(0,12,1,1,1,"Maison");
        // dessiner_maison();
        dessiner_plan1();
    }
    if(exemple>=2)
    {
        exit(-1);
    }

    trace_grille(5);
    glutSwapBuffers();
}

void animer()
{
    angle += .5 * sens_rotation;
    if(angle > 360)
        angle = 0;
    glutPostRedisplay();
}

void gererClavier(unsigned char touche, int x, int y)
{
    printf(" Touche: %c    Souris : %d %d \n",touche,x,y);

    if(touche=='a')
        sens_rotation*=-1; //On inverse le sens
    if(touche=='c')
        exemple++;
}

void transformer_polyone_actuel(Matrice m)
{
    int i;

    for(i=0; i<nombre_sommets; i++)
    {
        sommet[i]=produit_point(m,sommet[i]);        
    }
    init_lct();
    remplissage();
    balayage();
    glFlush();
    getchar();
    glClear(GL_COLOR_BUFFER_BIT);
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