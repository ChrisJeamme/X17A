#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "decor.h"
#include "karbre.h"
#include "boule.h"

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50 
#define SENS_MONTRE 1
#define SENS_INVERSE -1
#define MENU_RESET 1
#define MENU_QUITTER 2

void initGL();
void majVecteurs();
void Animer();
void Affichage();
void GererClavier(unsigned char touche, int x, int y);
void GestionSpecial(int key, int x, int y);
int appartientPlateforme(float x, float y, float z);
void vRappelSousMenu1(int i);
void vRappelMenuPrincipal(int i);
void gestionMenu();
void AffichageMenu();
void GererClavierMenu(unsigned char touche, int x, int y);
void lancement();
void lancementJeu();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    initGL();

    lancement();

    return 0;
}

void initGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("La boule magique");
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glGenTextures(2,tex_sol);
    glBindTexture(GL_TEXTURE_2D, tex_sol[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    chargementTexture(&tex_sol[0], "test.png");
    //chargementTexture(&tex_sol[1], "test.png");
}

void majVecteurs()
{
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
    //Position de l'observateur
    if(!appartientPlateforme(bx, by + brayon*5, bz))
    {
        ox = bx;
        oy = by + brayon*5;
        oz = bz;
    }
}


void lancement()
{
    //Menu
    glutDisplayFunc(AffichageMenu);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavierMenu); //<= Lancera lancementJeu
    glutMainLoop();
}

void lancementJeu()
{
    majVecteurs();
    gestionMenu();

    nb_plateformes = 0;

    point p11 = nouveau_point(-30, 0, -30);
    point p12 = nouveau_point(-30, 0, 30);
    point p13 = nouveau_point(30, 0, 30);
    point p14 = nouveau_point(30, 0, -30);

    point p21 = nouveau_point(30, -10, 30);
    point p22 = nouveau_point(30, -20, 90);
    point p23 = nouveau_point(90, -20, 90);
    point p24 = nouveau_point(90, -10, 30);

    point p31 = nouveau_point(30, 0, 150);
    point p32 = nouveau_point(90, 0, 150);

    point p41 = nouveau_point(90, -20, 90);
    point p42 = nouveau_point(90, -20, 150);
    point p43 = nouveau_point(150, 0, 150);
    point p44 = nouveau_point(150, 0, 90);

    ajouter_plateforme(p11, p12, p13, p14);
    ajouter_plateforme(p21, p22, p23, p24);
    ajouter_plateforme(p31, p22, p23, p32);
    ajouter_plateforme(p41, p42, p43, p44);



    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavier);
    glutSpecialFunc(GestionSpecial);

    glutMainLoop();
}

//Fonction Affichage pour flutDisplayFunc

void Affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix() ;
    glLoadIdentity();
    //afficher_vecteurs();

    glFrustum(-1,1,-1,1,1,200);

    // char vx_string[50];
    // sprintf(vx_string, "%f", vx);
    // afficherText(10,0,0,1,1,vx_string);

    maj_position_boule();
    
    ax=0; ay=0; az=0;

    //maj caméra
    // float positionCameraX = bx-vx*400;//((bx-vx*400)>7)?bx-vx-7:((bx-vx*400)<-7)?bx-vx+7:bx-vx*400;
    // float positionCameraY = by+brayon*4;
    // float positionCameraZ = bz-vz*400;//((bz-vz*400)>7)?bz-vz-7:((bz-vz*400)<-7)?bz-vz+7:bz-vz*400;

    //Mise a jour de la caméra
    maj_observateur();
    gluLookAt(ox, oy, oz, bx, by+brayon, bz+1, 0, 1, 0);
    //printf("Vecteur caméra: %f %f %f\n", ox, oy, oz);


    //Affichage Boule
    dessiner_boule(brayon,bx,by,bz);

    afficher_plateformes();
    afficher_decor();

    trace_grille(5);
    glutSwapBuffers();
}

void AffichageMenu()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,1,200);
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 1, 0);
    afficherText(1,0.1,1,1,1,"Boule Magique");
    afficherText(1,0,1,1,1,"Appuyez sur L pour lancer");
    glutSwapBuffers();
}

void Animer()
{
    glutPostRedisplay();
}

//Gestion clavier

void GestionSpecial(int key, int x, int y)
{ 	
    float normeVitesse = sqrt(vx*vx+vz*vz);
    if (key == GLUT_KEY_LEFT) //A gauche
    {
        float changementDirectionX = vz;
        float changementDirectionZ = -vx;
        ax = changementDirectionX*0.1;
        az = changementDirectionZ*0.1;
    }

    if (key == GLUT_KEY_UP) // On accelère
    {
        if (normeVitesse < 0.01) //La boule est à l'arrêt, il faut choisir une direction au hasard
        {     
            vx = 0.01;
            vz = 0.01;
        }
        else //On augmente le vecteur vitesse dans la même direction
        {
            ax = vx*0.2;
            az = vz*0.2;
        }
    } 

    if (key == GLUT_KEY_RIGHT)  //A droite
    {
        float changementDirectionX = -vz;
        float changementDirectionZ = vx;
        ax = changementDirectionX*0.1;
        az = changementDirectionZ*0.1;
    }

    if (key == GLUT_KEY_DOWN) //On veut ralentir
    {
        if (normeVitesse > 0.01)
        {
            ax -= vx*0.1;
            az -= vz*0.1;
        }
        else 
        {
            vx=0;
            vz=0;
        }
    }

} 

void GererClavierMenu(unsigned char touche, int x, int y)
{
    if(touche=='l')
    {
        lancementJeu();
    }
}

void GererClavier(unsigned char touche, int x, int y)
{
    //printf(" Touche: %c    Souris : %d %d \n",touche,x,y);

    //printf("AVANT: ax=%f az=%f\n, (bx=%f & bz=%f & bx/bz=%f & bz/bx=%f)",ax,az,bx,bz,bx/bz,bz/bx);

    float normeVitesse = sqrt(vx*vx+vz*vz);
    if(touche=='z') //On veut accélerer
    {
        if (normeVitesse < 0.01) //La boule est à l'arrêt, il faut choisir une direction au hasard
        {     
            vx = 0.01;
            vz = 0.01;
        }
        else //On augmente le vecteur vitesse dans la même direction
        {
            ax = vx*0.1;
            az = vz*0.1;
        }
    }
        
    if(touche=='s') //En veut décelérer
    {
        if (normeVitesse > 0.01)
        {
            ax -= vx*0.1;
            az -= vz*0.1;
        }
        else 
        {
            vx=0;
            vz=0;
        }
    }

    if(touche=='q') //A gauche
    {
        float changementDirectionX = vz;
        float changementDirectionZ = -vx;
        ax = changementDirectionX*0.1;
        az = changementDirectionZ*0.1;
    }
    
    if(touche=='d') //A droite
    {
        float changementDirectionX = -vz;
        float changementDirectionZ = vx;
        ax = changementDirectionX*0.1;
        az = changementDirectionZ*0.1;
    }
    
    //Intteruption
    if(touche=='g')
        getchar();

    //Reset de la boule
    if(touche=='r')
    {
        vx=0;        vy=0;        vz=0;
        bx=1;        by=50;        bz=1;
    }


    if (touche ==27) //Touche Echap => ferme le programme
		exit(0);
}

//

int appartientPlateforme(float x, float y, float z)
{
    return 0;
    // int i;
    // for (i=0; i<nb_plateformes; i++)
    // {
    //     int x1 = tab_plateformes[i].x1;
    //     int y1 = tab_plateformes[i].y1;
    //     int z1 = tab_plateformes[i].z1;
    //     int x2 = tab_plateformes[i].x2;
    //     int y2 = tab_plateformes[i].y2;
    //     int z2 = tab_plateformes[i].z2;
    
       
    // }
}

//Menu ingame

void gestionMenu()
{
    // nSousmenu1 = glutCreateMenu(vRappelSousMenu1);
	// glutAddMenuEntry("Elément 1 du sous-menu 1", 11);
	nMenuprincipal = glutCreateMenu(vRappelMenuPrincipal);
	// glutAddSubMenu("Sous-menu 1", nSousmenu1);
    glutAddMenuEntry("Reset", MENU_RESET);
	glutAddMenuEntry("Quitter", MENU_QUITTER);
	// glutAddMenuEntry("Elément 2", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void vRappelSousMenu1(int i)
{
	printf("rappel de l'element %d\n", i);
}

void vRappelMenuPrincipal(int i)
{
    if(i==MENU_QUITTER)
        exit(0);
    if(i==MENU_RESET)
    {
        vx=0;        vy=0;        vz=0;
        bx=1;        by=50;        bz=1;
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