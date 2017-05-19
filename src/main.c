#include "jeu.h"
#include "niveaux.h"

int main(int argc, char** argv)
{
    //Analyse & interprétation des arguments
    gestion_arguments(argc,argv);
    //Initialisation de rand
    srand(time(NULL));
    //Initialisation de la librairie GLUT
    glutInit(&argc, argv);
    //Paramètres d'initalisation et des objets
    initGL();
    //Importation des niveaux du dossier ./level/
    importer_niveaux();
    //Fonction d'affichage des niveaux chargés
    afficher_niveaux();
    //Lancement du menu
    lancement();
    return 0;
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