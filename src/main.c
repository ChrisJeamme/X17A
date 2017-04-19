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

void Animer();
void Affichage();
void GererClavier(unsigned char touche, int x, int y);
void GestionSpecial(int key, int x, int y);

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
    //Position de l'observateur
    ox = bx;
    oy = by + brayon*5;
    oz = bz;

    nb_plateformes = 0;

    ajouter_plateforme(-30,0,-30,30,0,30);
    ajouter_plateforme(30,-10,30,90,-20,90);
    ajouter_plateforme(90,-20,90,30,-15,150);
    ajouter_plateforme(40,-30,95,150,-10,150);

    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavier);
    glutSpecialFunc(GestionSpecial);

    glutMainLoop();
    return 0;
}


void Affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix() ;
    glLoadIdentity();
    //afficher_vecteurs();

    glFrustum(-1,1,-1,1,1,100);

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
    
    trace_grille(5);
    glutSwapBuffers();
}

void Animer()
{
    glutPostRedisplay();
}

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
            ax = vx*0.1;
            az = vz*0.1;
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

// void GererClavier(unsigned char touche, int x, int y)
// {
//     printf(" Touche: %c    Souris : %d %d \n",touche,x,y);

//     printf("AVANT: ax=%f az=%f\n, (bx=%f & bz=%f & bx/bz=%f & bz/bx=%f)",ax,az,bx,bz,bx/bz,bz/bx);

//     double angle;

//     if(touche=='z') //On veut accélerer
//     {
//         if(vx==0)
//         {
//             az = 0.01;
//             ax = 0;
//         }
//         else
//         {
//             if(vz==0)
//             {
//                 az = 0;
//                 ax = 0.01;
//             }
//             else
//             {
//                 angle = acos(0.01*vz / (sqrt(vz*vz+vx*vx)*sqrt(0.01*0.01)));
//                 az = 0*sin(angle)+0.01*cos(angle);
//                 ax = 0*cos(angle)-0.01*sin(angle);
//             }
//         }
//     }
        
//     if(touche=='s') //En veut décelérer
//     {
//         if(vx==0)
//         {
//             az = -0.01;
//             ax = 0;
//         }
//         else
//         {
//             if(vz==0)
//             {
//                 az = 0;
//                 ax = -0.01;
//             }
//             else
//             {
//                 angle = acos(0.01*vz / (sqrt(vz*vz+vx*vx)*sqrt(0.01*0.01)));
//                 az = -(0*sin(angle)+0.01*cos(angle));
//                 ax = -(0*cos(angle)-0.01*sin(angle));
//             }
//         }
//     }

//     if(touche=='q') //A gauche
//     {
//         if(vx==0)
//         {
//             az = 0;
//             ax = 0.01;
//         }
//         else
//         {
//             if(vz==0)
//             {
//                 az = 0.01;
//                 ax = 0;
//             }
//             else
//             {
//                 angle = acos(0.01*vz / (sqrt(vz*vz+vx*vx)*sqrt(0.01*0.01)));
//                 az = -(0*cos(angle)-0.01*sin(angle));
//                 ax = -(0*sin(angle)+0.01*cos(angle));
//             }
//         }
//     }
    
//     if(touche=='d') //A droite
//     {
//         if(vx==0)
//         {
//             az = 0;
//             ax = -0.01;
//         }
//         else
//         {
//             if(vz==0)
//             {
//                 az = -0.01;
//                 ax = 0;
//             }
//             else
//             {
//                 angle = acos(0.01*vz / (sqrt(vz*vz+vx*vx)*sqrt(0.01*0.01)));
//                 az = 0*cos(angle)-0.01*sin(angle);
//                 ax = (0*sin(angle)+0.01*cos(angle));
//             }
//         }
//     }
    
//     //Intteruption
//     if(touche=='g')
//         getchar();

//     //Reset de la boule
//     if(touche=='r')
//     {
//         vx=0;        vy=0;        vz=0;
//         bx=1;        by=50;        bz=1;
//     }

//     printf("APRES: ax=%f az=%f\n",ax,az);

//     if (touche ==27) //Touche Echap => ferme le programme
// 		exit(0);
// }



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