#include "boule.h"

/*Calcule si la boule est en collision avec un des plan*/
int collision_boule_plateforme()
{
    int i;
    for (i=0; i<nb_plateformes; i++) //On parcourt les plateforme dans le tableau
    {
        //On récupère 3 points qui forment la plateforme
        int x1 = tab_plateformes[i].p1.x;
        int y1 = tab_plateformes[i].p1.y;
        int z1 = tab_plateformes[i].p1.z;

        int x2 = tab_plateformes[i].p2.x;
        int y2 = tab_plateformes[i].p2.y;
        int z2 = tab_plateformes[i].p2.z;

        int x3 = tab_plateformes[i].p3.x;
        int y3 = tab_plateformes[i].p3.y;
        int z3 = tab_plateformes[i].p3.z;

        //On regarde la position de la boule en x et z par rapport à la plate-forme
        if ((bx < min(x1,x2,x3) )||( bx > max(x1,x2,x3) )||( bz < min(z1,z2,z3) )||( bz > max(z1,z2,z3)))
           continue;    //si elle est pas au-dessus, on vérifie avec la plateforme suivante

        //Vecteur AB
        float ABx = x1 - x2;
        float ABy = y1 - y2;
        float ABz = z1 - z2;

        //Vecteur AC
        float ACx = x3 - x2;
        float ACy = y3 - y2;
        float ACz = z3 - z2;

        //Produit vectoriel pour avoir vecteur normal au plan (ABC): 
        float a = ABy*ACz - ABz*ACy;
        float b = ABz*ACx - ABx*ACz;
        float c = ABx*ACy - ABy*ACx;
        float d = -(a*x1 + b*y1 + c*z1); //car (x1,y1,z1) appartient au plan

        //Vecteur (A, centre de la boule)
        float Abx = bx - x1; 
        float Aby = by - y1; 
        float Abz = bz - z1;

        //On calcule la distance entre la boule et la plateforme
        float distance = fabs((Abx*a + Aby*b + Abz*c)/sqrt(a*a + b*b + c*c));

        if (distance > brayon) //La boule est au dessus ou en dessous de la platforme mais ne la touche pas
            continue;   //On vérifie avec une autre plate-forme
        else //On est sur la plate-forme
        {
            if (y1 != y2 || y1 != y3)   //Si la plate-forme n'est pas plate
                ajouter_pente(a,b,c);   //On ajoute la pente aux vecteurs de la boule
            by = ((-a*bx-c*bz-d)/b)+brayon; //On place la boule sur la plate-forme
            return 1; //On renvoit que la boule est sur une plate-forme
        }
    }
    return 0; //On a trouvé aucun plate-forme telle que la boule soit en collision. On renvoit 0.
}

/*On modifie les vecteurs de la boule en fonction de la pente de la plate-forme*/
void ajouter_pente(int a, int b, int c) 
{   
    //On cherche le vecteur directeur normé de la pente
    //Vecteur pente
    float Px = a*b;
    float Py = a*a + c*c;
    float Pz = c*b;
    float norme = sqrt(Px*Px + Py*Py + Pz*Pz);
    //Vecteur normé
    Px /= norme;
    //Py /= norme;
    Pz /= norme;
    if (Px != 0)
        Px = 1/Px;
    if (Pz != 0)
        Pz = 1/Pz;
    vx += Px*0.0001;
    vz += Pz*0.0001;
}

/*Met a jour le vecteur vitesse*/
void maj_vecteur_vitesse()
{
    vx = vx + ax;//On ajoute l'acceleration
    vy = vy + ay + gy; 
    vz = vz + az;
    //printf("\n\n VITESSE X : %f \n VITESSE Z : %f\n\n",vx, vz);
}

/*Met a jour la postion de la boule*/
void maj_position_boule()
{
    maj_vecteur_vitesse(); //on récupere le vecteur vitesse
    bx+=vx; //on ajoute la composante x de la vitesse a la position de la boule en x
    if (!collision_boule_plateforme()) //La boule n'est pas en collision avec une plateforme
    {
        by+= vy; //On modifie la position en fonction du vecteur vitesse en y (la gravité entre en jeu !)
    }
    else
    {
        vy = 0; //On est sur une plate-forme, il ne faut pas descendre en dessous
    }
    bz+=vz; //pareil que pour x
}

/*Met a jour la position de l'observateur*/
void maj_observateur()
{
    ox = bx - vx*200;
    oz = bz - vz*200;
    oy = by + brayon*5;
}

/*maximum entre 3 entiers*/
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

/*minimum entre 3 entiers*/
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

/*Fonction de débeugage*/
void afficher_vecteurs()
{
    printf("Position : \n   %3f, %3f, %3f\n", bx, by, bz);
    printf("Vitesse : \n   %3f, %3f, %3f\n", vx, vy, vz);
    printf("Acceleration : \n   %3f, %3f, %3f\n", ax, ay, az);
}