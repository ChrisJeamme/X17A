#include "boule.h"

#define EXTERIEUR 0
#define INTERSECTION 1
#define INTERIEUR 2

int intersection_plan_boule(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int x3 = x2;
    int y3 = y1;
    int z3 = z3;

    float ABx = x2 - x1;
    float ABy = y2 - y1;
    float ABz = z2 - z1;

    float ACx = x3 - x1;
    float ACy = y3 - y1;
    float ACz = z3 - z1;

    //Produit vectoriel pour avoir vecteur normal au plan (ABC): 
    float a = ABy*ACz - ABz*ACy;
    float b = ABz*ACx - ABx*ACz;
    float c = ABx*ACy - ABy*ACx;
    //float d = -(a*x1 + b*x2 + c*x3); //car (x1,x2,x3) appartient au plan

    float Abx = bx - x1; 
    float Aby = by - y1; 
    float Abz = bz - z1;

    float distance = abs((Abx*a + Aby*b + Abz*c)/sqrt(a*a + b*b + c*c));


    if (distance > brayon)
        return 0;
    if ((bx < x1 && bx < x2 )||( bx > x1 && bx > x2 )||( bz < z1 && bz < z2 )||( bz > z1 && bz > z2))
        return 0;
    else return 1;
}

void maj_vecteur_vitesse()
{
    vx = vx + ax;
    if (vx > 0.05 || vx < -0.05)
        vx -= ax;
    vy = vy + ay + gy;
    vz = vz + az;
    if (vz > 0.05 || vz < -0.05)
        vz -= az;
    //printf("\n\n VITESSE X : %f \n VITESSE Z : %f\n\n",vx, vz);
}

void maj_position_boule()
{
    bx+=vx;
    if (!intersection_plan_boule(-30,0,-30,30,0,30))
    {
        by+= vy;
    }
    else    //Boule au sol
        vy = 0;
    bz+=vz;
}

void maj_observateur()
{

    ox = bx - vx*400;
    oz = bz - vz*400;
    oy = by + brayon * 5;
}

void afficher_vecteurs()
{
    printf("Position : \n   %3f, %3f, %3f\n", bx, by, bz);
    printf("Vitesse : \n   %3f, %3f, %3f\n", vx, vy, vz);
    printf("Acceleration : \n   %3f, %3f, %3f\n", ax, ay, az);
}