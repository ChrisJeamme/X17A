#include "boule.h"

int collision_boule_plateforme()
{
    int i;
    for (i=0; i<nb_plateformes; i++)
    {
        int x1 = tab_plateformes[i].p1.x;
        int y1 = tab_plateformes[i].p1.y;
        int z1 = tab_plateformes[i].p1.z;

        int x2 = tab_plateformes[i].p2.x;
        int y2 = tab_plateformes[i].p2.y;
        int z2 = tab_plateformes[i].p2.z;

        int x3 = tab_plateformes[i].p3.x;
        int y3 = tab_plateformes[i].p3.y;
        int z3 = tab_plateformes[i].p3.z;

       if ((bx < min(x1,x2,x3) )||( bx > max(x1,x2,x3) )||( bz < min(z1,z2,z3) )||( bz > max(z1,z2,z3)))
           continue;

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
        float d = -(a*x1 + b*y1 + c*z1); //car (x1,y1,z1) appartient au plan

        float Abx = bx - x1; 
        float Aby = by - y1; 
        float Abz = bz - z1;

        float distance = fabs((Abx*a + Aby*b + Abz*c)/sqrt(a*a + b*b + c*c));

        if (distance > brayon)
            continue;
        else 
        {
            if (y1 != y2)
                ajouter_pente(a,b,c);
            by = ((-a*bx-c*bz-d)/b)+brayon;
            return 1;
        }
    }
    return 0;
}

int max(int x1, int x2, int x3)
{
    if (x1>x2)
        if (x1>x3)
            return x1;
        else return x3;
    else if (x2>x3)
            return x2;
        else return x3;
}

int min(int x1, int x2, int x3)
{
    if (x1<x2)
        if (x1<x3)
            return x1;
        else return x3;
    else if (x2<x3)
            return x2;
        else return x3;
}


void ajouter_pente(int a, int b, int c) //on cherche le vecteur directeur normé de la pente
{   
    float Px = a*b;
    float Py = a*a + c*c;
    float Pz = c*b;
    float norme = sqrt(Px*Px + Py*Py + Pz*Pz);
    Px /= norme;
    Py /= norme;
    Pz /= norme;
    vx += Px*0.0001;
    vz += Pz*0.0001;
}

void maj_vecteur_vitesse()
{
    vx = vx + ax;
    if (vx > 0.1 || vx < -0.1)
        vx -= ax;
    vy = vy + ay + gy;
    vz = vz + az;
    if (vz > 0.1 || vz < -0.1)
        vz -= az;
    //printf("\n\n VITESSE X : %f \n VITESSE Z : %f\n\n",vx, vz);
}

void maj_position_boule()
{
    maj_vecteur_vitesse();
    bx+=vx;
    if (!collision_boule_plateforme()) //La boule n'est pas en collision avec une plateforme
    {
        by+= vy;
    }
    else
    {
        vy = 0;
    }
    bz+=vz;
}

void maj_observateur()
{
    ox = bx - vx*400;
    oz = bz - vz*400;
    oy = by + brayon*5;
}

void afficher_vecteurs()
{
    printf("Position : \n   %3f, %3f, %3f\n", bx, by, bz);
    printf("Vitesse : \n   %3f, %3f, %3f\n", vx, vy, vz);
    printf("Acceleration : \n   %3f, %3f, %3f\n", ax, ay, az);
}