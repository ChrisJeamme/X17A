#include "GL/gl.h"
#include "GL/glut.h"
#include "point.h"

#define HAUTEUR_FENETRE 800 
#define LARGEUR_FENETRE 800
#define TAILLE 50

//Variables globales

    Point *sommet;
    Cote *lc;
    int *e; //Rangs pour LCE
    int *s; //Rangs pour LCS
    int *t; //Rangs pour LCT
    int next_lct;
    int nombre_sommets;

    //Note: LCS LCS LCT sont des tableaux d'entiers représentants les numéros des sommets du tableau LC

//Prototypes

    void definir_polygone_affiche(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
    void definir_polygone_affiche_point(Point p1, Point p2, Point p3, Point p4);
    void Affichage();
    //Fonction de tracage d'un point de côte 2n
    void trace_point(int x, int y, int n);
    //Tracage de la grille des points
    void trace_grille(int n);
    //Retourne le plus grand entre a et b
    float max(float a, float b);
    //Retourne le plus grand entre a et b
    float min(float a, float b);
    //Trace le segment entre x1 et x2
    void segment(int x1, int x2, int y) ;
    //Lance le remplissage de LC LCS LCE
    void remplissage();
    //Récupère la liste de côté et la stock dans LC
    void get_lc();
    //Tri LCE
    void trier_lce();
    //Tri LCS
    void trier_lcs();
    //Test l'appartenance à un côté d'un point
    int appartient_cote(int numero_cote, int xa, int ya);
    //Initialise LCT
    void init_lct();
    //Ajouter un côté dans LCT
    void ajout_lct(int num_cote);
    //Supprime un côté de LCT
    void suppression_lct(int num_cote);
    //On cherche le ymin le plus petit
    int balayage_limite_basse();
    //On cherche le ymin le plus grand
    int balayage_limite_haute();
    //Teste si un côté à un coef directeur nul
    int coef_dir_nul(int numero_cote);
    //Donne le X du point d'intersection avec un coté au niveau Y
    float interection_y_cote(int numero_cote, int y);  //Renvoi le x
    //Fonction principale du balayage pour le remplissage
    void balayage();