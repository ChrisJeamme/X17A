#include "menu.h"

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

void gestionMenu() //choix_niveau(int choix_niveau)
{
    nSousmenuChoixNiveau = glutCreateMenu(vRappelSousmenuChoixNiveau);

    String chaine;
    for(i=1; i<=nombre_niveau; i++)
    {
        sscanf(chaine,"Niveau %d",i);
        glutAddMenuEntry(chaine, i);
    }
	nMenuprincipal = glutCreateMenu(vRappelMenuPrincipal);
	glutAddSubMenu("Choix du niveau", choix_niveau);
    glutAddMenuEntry("Reset", MENU_RESET);
	glutAddMenuEntry("Quitter", MENU_QUITTER);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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