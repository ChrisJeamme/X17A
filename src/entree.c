#include "entree.h"
#include "jeu.h"

void GestionSpecial(int key, int x, int y)
{ 	
    float normeVitesse = sqrt(vx*vx+vz*vz);
    if (key == GLUT_KEY_LEFT) //A gauche
    {
        if (vx == 0 && vz == 0) //La boule est à l'arret
        {
            float dxp = cos(-0.1)*dx - sin(-0.1)*dz;
            dz = sin(-0.1)*dx + cos(-0.1)*dz;
            dx = dxp;
        }
        float vxp = cos(-0.1)*vx - sin(-0.1)*vz;
        vz = sin(-0.1)*vx + cos(-0.1)*vz;
        vx = vxp;
    }

    if (key == GLUT_KEY_UP) // On accelère
    {
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

    if (key == GLUT_KEY_RIGHT)  //A droite
    {
        if (vx == 0 && vz == 0) //La boule est à l'arret
        {
            float dxp = cos(0.1)*dx - sin(0.1)*dz;
            dz = sin(0.1)*dx + cos(0.1)*dz;
            dx = dxp;
        }
        float vxp = cos(0.1)*vx - sin(0.1)*vz;
        vz = sin(0.1)*vx + cos(0.1)*vz;
        vx = vxp;
    }

    if (key == GLUT_KEY_DOWN) //On veut ralentir
    {
        if (normeVitesse > 0.005)
        {
            ax -= vx*0.1;
            az -= vz*0.1;
            dx = vx;
            dz = vz;
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
    if(touche=='l' || touche == 13 || touche == 32) //L ou Espace ou Entree
    {
        lancementJeu();
    }
    if (touche == 27) //Touche Echap => ferme le programme
    {
        exit(0);
    }
}

void GererClavier(unsigned char touche, int x, int y)
{
    //printf(" Touche: %c    Souris : %d %d \n",touche,x,y);

    //printf("AVANT: ax=%f az=%f\n, (bx=%f & bz=%f & bx/bz=%f & bz/bx=%f)",ax,az,bx,bz,bx/bz,bz/bx);

    float normeVitesse = sqrt(vx*vx+vz*vz);
    if(touche=='z') //On veut accélerer
    {
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
        
    if(touche=='s') //En veut décelérer
    {
        if (normeVitesse > 0.01)
        {
            ax -= vx*0.1;
            az -= vz*0.1;
            dx = vx;
            dz = vz;
        }
        else 
        {
            vx=0;
            vz=0;
        }
    }

    if(touche=='q') //A gauche
    {
        if (vx == 0 && vz == 0) //La boule est à l'arret
        {
            float dxp = cos(-0.1)*dx - sin(-0.1)*dz;
            dz = sin(-0.1)*dx + cos(-0.1)*dz;
            dx = dxp;
        }
        float vxp = cos(-0.1)*vx - sin(-0.1)*vz;
        vz = sin(-0.1)*vx + cos(-0.1)*vz;
        vx = vxp;
    }
    
    if(touche=='d') //A droite
    {
        if (vx == 0 && vz == 0) //La boule est à l'arret
        {
            float dxp = cos(0.1)*dx - sin(0.1)*dz;
            dz = sin(0.1)*dx + cos(0.1)*dz;
            dx = dxp;
        }
        float vxp = cos(0.1)*vx - sin(0.1)*vz;
        vz = sin(0.1)*vx + cos(0.1)*vz;
        vx = vxp;
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