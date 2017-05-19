#include "entree.h"
#include "jeu.h"

/*Pour tourner à droite*/
void droite()
{
    //Modification de la direction
    float dxp = cos(0.1)*dx - sin(0.1)*dz;
    dz = sin(0.1)*dx + cos(0.1)*dz;
    dx = dxp;

    //Modification du vecteur vitesse
    float vxp = cos(0.1)*vx - sin(0.1)*vz;
    vz = sin(0.1)*vx + cos(0.1)*vz;
    vx = vxp;
}

/*Pour tourner à gauche*/
void gauche()
{
    //Modification de la direction
    float dxp = cos(-0.1)*dx - sin(-0.1)*dz;
    dz = sin(-0.1)*dx + cos(-0.1)*dz;
    dx = dxp;

    //Modification du vecteur vitesse
    float vxp = cos(-0.1)*vx - sin(-0.1)*vz;
    vz = sin(-0.1)*vx + cos(-0.1)*vz;
    vx = vxp;
}

/*Pour accélerer*/
void accelere()
{
    float normeVitesse = sqrt(vx*vx+vz*vz);
    if (normeVitesse == 0) //La boule est à l'arrêt, il faut choisir une direction au hasard
    {
        float normeDirection = sqrt(dx*dx+ dz*dz);     
        vx = dx/normeDirection * 0.01;
        vz = dz/normeDirection * 0.01;
    }
    else //On augmente le vecteur vitesse dans la même direction
    {
        //On calcule la norme du vecteur vitesse
        if (normeVitesse < 0.1) //On a pas atteint la vitesse max
        {
            ax = vx*0.2;
            az = vz*0.2;
        }
    }
}

/*Pour ralentir*/
void decelere()
{
    float normeVitesse = sqrt(vx*vx+vz*vz);
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

/*Fonctions qui gère les touches flechées*/
void GestionSpecial(int key, int x, int y)
{ 	
    if (key == GLUT_KEY_LEFT) //A gauche
        gauche();

    if (key == GLUT_KEY_UP) // On accelère
        accelere();

    if (key == GLUT_KEY_RIGHT)  //A droite
        droite();

    if (key == GLUT_KEY_DOWN) //On veut ralentir
        decelere();
} 

/*Gestion des touches normales*/
void GererClavier(unsigned char touche, int x, int y)
{
    if(touche=='z') //On veut accélerer
        accelere();
        
    if(touche=='s') //En veut décelérer
        decelere();

    if(touche=='q') //A gauche
        gauche();
    
    if(touche=='d') //A droite
        droite();
    
    //Intteruption
    if(touche=='g')
        getchar();

    //Reset de la boule
    if(touche=='r')
    {
        vx=0;       vy=0;       vz=0;
        bx=start.x; by=start.y; bz=start.z;
    }


    if (touche ==27) //Touche Echap => ferme le programme
		exit(0);
}

/*Gère le menu*/
void GererClavierMenu(unsigned char touche, int x, int y)
{
    if(touche=='l' || touche == 13 || touche == 32) //L ou Espace ou Entree
    {
        lancementJeu();
    }
    if (touche == 27) //Touche Echap => ferme le programme
    {
        exit(0);
    }
}