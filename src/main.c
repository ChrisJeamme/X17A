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



void transformer_polyone_actuel(Matrice m);
void animer();
void Affichage();
void gererClavier(unsigned char touche, int x, int y);
void afficher_vecteurs();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("La boule magique");
    glEnable(GL_DEPTH_TEST);

    //Rayon de la boule
    brayon = 2;
    //Coordonnées du centre de la boule
    bx = 0;
    by = 50;
    bz = 0;
    //Vecteur de vitesse de la boule
    vx = 0;
    vy = 0;
    vz = 0;
    //Vecteur d'accélération de la boule
    ax = 0;
    ay = 0;
    az = 0;
    //Vecteur de gravité de la boule
    gx = 0;
    gy = -0.001;
    gz = 0;



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
    afficher_vecteurs();

    glFrustum(-1,1,-1,1,1,100);
    vx = vx + ax;
    vy = vy + ay + gy;
    vz = vz + az;
    
    bx+=vx;
    if (!intersection_plan_boule(-30,0,-30,30,0,30))
    {
        by+= vy;
    }
    else 
        vy = 0;
    bz+=vz;

    ax=0; ay=0; az=0;

    gluLookAt(bx-vx*400, by+brayon*4, bz-vz*400, bx, by+brayon, bz+1, 0, 1, 0);
    
    dessiner_plan(-30,0,-30,30,0,30);
    dessiner_boule(brayon,bx,by,bz);

    trace_grille(5);
    glutSwapBuffers();
}

void animer()
{
    glutPostRedisplay();
}

void gererClavier(unsigned char touche, int x, int y)
{
    printf(" Touche: %c    Souris : %d %d \n",touche,x,y);

    if(touche=='z') //On veut accélerer
        az += 0.01;  
    if(touche=='s') //En veut décelérer
        if (vz >0) //Si vitesse positive
            az -= 0.01;  //On décrémente l'accélération donc la vitesse va diminuer


    if(touche=='q') //A gauche
        ax -= 0.01;
    if(touche=='d') //A droite
        ax += 0.01;

    if (touche ==27) //Touche Echap => ferme le programme
		exit(0);
}


void afficher_vecteurs()
{
    printf("Position : \n   %3f, %3f, %3f\n", bx, by, bz);
    printf("Vitesse : \n   %3f, %3f, %3f\n", vx, vy, vz);
    printf("Acceleration : \n   %3f, %3f, %3f\n", ax, ay, az);
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