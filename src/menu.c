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