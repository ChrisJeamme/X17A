#include "point.h"
#include "matrice.h"

#define PI 3.14159

Matrice creer_matrice();
Pointf copier_pointf(Pointf p);
Point creer_point(int x, int y, int z);
Pointf creer_pointf(float x, float y, float z);
Pointf addition_pointf(Pointf p1, Pointf p2);
Matrice produit(Matrice a, Matrice b);
void afficher_matrice(Matrice m);
void afficher_point(Point p);
Point produit_point(Matrice a, Point p);
Matrice changement_echelle_matrice(Point echelle);
Point changement_echelle(Point p, Point echelle);
Matrice translater(Point vecteur);
Matrice matrice_rotation(double angle);
Matrice matrice_rotation_point(double angle, Point p_reference);
Point rotation_point(Point p, Point p_reference, double angle);