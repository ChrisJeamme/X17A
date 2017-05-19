#include "menu.h"

/*Affiche le menu (niveauxcipal)*/
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

/*Gère le menu clic droit*/
void gestionMenu() //choix_niveau(int choix_niveau)
{
    nSousmenuChoixNiveau = glutCreateMenu(vRappelSousmenuChoixNiveau);

    int i;
    for(i=0; i<nombre_niveau; i++)
    {
        glutAddMenuEntry("Niveau ?", i);
    }
	nMenuniveauxcipal = glutCreateMenu(vRappelMenuniveauxcipal);
	glutAddSubMenu("Choix du niveau", nSousmenuChoixNiveau);
    glutAddMenuEntry("Reset", MENU_RESET);
	glutAddMenuEntry("Quitter", MENU_QUITTER);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*Sous menu pour le choix de niveau*/
void vRappelSousmenuChoixNiveau(int i)
{
    choix_niveau(i);
}

/*Menu clic droit*/
void vRappelMenuniveauxcipal(int i)
{
    if(i==MENU_QUITTER)
        exit(0);
    if(i==MENU_RESET)
    {
        if(start!=NULL)
        {
            vx=0;        vy=0;        vz=0;
            bx=start.x;  by=start.y;  bz=start.z;
        }
       
    }

}