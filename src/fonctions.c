#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fonctions.h"

Matrice creer_matrice()
{
    Matrice m = (Matrice) malloc(sizeof(Matrice)*3);
    int i;
    for(i=0; i<3; i++)
    {
        m[i] = (float*) malloc(sizeof(float*)*3);
    }
    return m;
}

Pointf copier_pointf(Pointf p)
{
    return creer_pointf(p.x, p.y, p.z);
}

Point creer_point(int x, int y, int z)
{
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

Pointf creer_pointf(float x, float y, float z)
{
    Pointf p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

Pointf addition_pointf(Pointf p1, Pointf p2)
{
    return creer_pointf(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);
}

void afficher_matrice(Matrice m)
{
    int i,j;
    for(i=0; i<3; i++)
    {
        printf("\t");
        for(j=0; j<3; j++)
        {
            printf("%f ",m[i][j]);
        }
        printf("\n");
    }
}

void afficher_point(Point p)
{
    printf("Point:\n\tX = %d\n\tY = %d\n\tZ = %d\n", p.x, p.y, p.z);
}

Matrice produit(Matrice a, Matrice b)
{
    Matrice m = creer_matrice();

    int i, j;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            m[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
        }
    }

    return m;
}

Point produit_point(Matrice a, Point p)
{
    Point resultat;
    resultat.x = (int) round(a[0][0]*p.x+a[0][1]*p.y+a[0][2]*p.z);
    resultat.y = (int) round(a[1][0]*p.x+a[1][1]*p.y+a[1][2]*p.z);
    resultat.z = (int) round(a[2][0]*p.x+a[2][1]*p.y+a[2][2]*p.z);
    return resultat;
}

Matrice changement_echelle_matrice(Point echelle)
{
    Matrice m1 = creer_matrice();
    m1[0][0]= echelle.x;    m1[0][1]= 0;            m1[0][2]= 0;
    m1[1][0]= 0;            m1[1][1]= echelle.y;    m1[1][2]= 0;
    m1[2][0]= 0;            m1[2][1]= 0;            m1[2][2]= echelle.z;
    return m1;
}

Point changement_echelle(Point p, Point echelle)
{
    return produit_point(changement_echelle_matrice(echelle), p);
}

Matrice translater(Point vecteur)
{
    Matrice m1 = creer_matrice();
    m1[0][0]= 1;                m1[0][1]= 0;                m1[0][2]= vecteur.x;
    m1[1][0]= 0;                m1[1][1]= 1;                m1[1][2]= vecteur.y;
    m1[2][0]= 0;                m1[2][1]= 0;                m1[2][2]= 1;
    return m1;
}

//Matrice pour rotation par rapport à l'origine
Matrice matrice_rotation(double angle)
{
    Matrice m1 = creer_matrice();
    m1[0][0]= cos(angle);   m1[0][1]= -sin(angle);  m1[0][2]= 0;
    m1[1][0]= sin(angle);   m1[1][1]= cos(angle);   m1[1][2]= 0;
    m1[2][0]= 0;            m1[2][1]= 0;            m1[2][2]= 1;
    return m1;
}

//Matrice de rotation par rapport à un point
Matrice matrice_rotation_point(double angle, Point p_reference)
{
    Matrice translat = translater(p_reference);
    Matrice tourne = produit(translat, matrice_rotation(angle));
    
    Point p_reference_inv;
    p_reference_inv.x = -p_reference.x;
    p_reference_inv.y = -p_reference.y;
    p_reference_inv.z = -p_reference.z;
    return produit(tourne, translater(p_reference_inv));
}

//Image d'un point par rapport à la matrice de rotation
Point rotation_point(Point p, Point p_reference, double angle)
{
    return produit_point(matrice_rotation_point(angle, p_reference), p);
}