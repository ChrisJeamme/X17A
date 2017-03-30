#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fonctions.h"
#include "volume.h"

#define EXTERIEUR 0
#define INTERSECTION 1
#define INTERIEUR 2

int position_cube_boule(Pointf centre_boule, int rayon_boule, Pointf p1, Pointf p2)
{
    float rayon_cube = distancef(p1,p2)/2;

    Pointf centre_cube;
        centre_cube.x = (p2.x+p1.x)/2;
        centre_cube.y = (p2.y+p1.y)/2;
        centre_cube.z = (p2.z+p1.z)/2;

    if(distancef(centre_boule,centre_cube)+rayon_cube < rayon_boule)
        return INTERIEUR;
    if(distancef(centre_boule,centre_cube) < rayon_boule+rayon_cube)
        return INTERSECTION;
    return EXTERIEUR;
}

karbre boule2arbre(Pointf centre_boule, int rayon_boule, Pointf p1, Pointf p2)
{
    return boule2karbre(centre_boule, rayon_boule, p1, p2, p2.x-p1.x);
}

karbre boule2karbre(Pointf centre_boule, int rayon_boule, Pointf p1, Pointf p2, float subdivision)
{
    /*  _________  p222
      /  5 /  6 /|
     /----/----/||
    /____/____/ || p212
    |  3 | 4  | ||
    |____|____|/|/ p202
    |  1 | 2  | / 
    |____|____|/
  p000  p100  p200
    */

    if(position_cube_boule(centre_boule,rayon_boule, p1, p2) == EXTERIEUR)
    {
        printf("EXTERIEUR\n");
        return kConsArbre(VIDE, kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide());
    }
    if(position_cube_boule(centre_boule,rayon_boule, p1, p2) == INTERIEUR)
    {
        printf("INTERIEUR\n");
        return kConsArbre(PLEIN, kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide());
    }
    if(subdivision<=1) //Cas d'arrêt pour la récursivité
        return kConsArbre(PLEIN, kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide());

    printf("RECURRE (p2.x-p1.x=%f)\n",p2.x-p1.x);

    //Sinon récursif, on boule2arbre, on divise par 8 et on kConsArbre(?, boule2karbre, boule2karbre ... *8)
    
    int x1=p1.x, x2=p2.x, y1=p1.y, y2=p2.y, z1=p1.z, z2=p2.z;
    return kConsArbre(INTERIEUR,
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf(x1,y1,(z1+z2)/2),
            creer_pointf((x1+x2)/2,(y1+y2)/2,z2), subdivision/2),
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf((x1+x2)/2,y1,(z1+z2)/2),
            creer_pointf(x2,(y1+y2)/2,z2), subdivision/2),
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf((x1+x2)/2,y1,z1),
            creer_pointf(x2, (y1+y2)/2,(z1+z2)/2), subdivision/2),
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf(x1,y1,z1),
            creer_pointf((x1+x2)/2,(y1+y2)/2, (z1+z2)/2), subdivision/2),

        boule2karbre(centre_boule, rayon_boule,
            creer_pointf(x1,(y1+y2)/2,(z1+z2)/2),
            creer_pointf((x1+x2)/2,y2,z2), subdivision/2),
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf((x1+x2)/2,(y1+y2)/2,(z1+z2)/2),
            creer_pointf(x2,y2,z2), subdivision/2),
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf((x1+x2)/2,(y1+y2)/2,z1),
            creer_pointf(x2,y2,(z1+z2)/2), subdivision/2),
        boule2karbre(centre_boule, rayon_boule,
            creer_pointf(x1,(y1+y2)/2,z1),
            creer_pointf((x1+x2)/2,y2, (z1+z2)/2), subdivision/2));
}

karbre intersection(karbre a1, karbre a2)
{
    int r1 = a1->racine;
    int r2 = a2->racine;

    if(r1 == VIDE || r2 == VIDE)
        return kConsArbre(VIDE, kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide());
    if(r1 == PLEIN)
        return a2;
    if(r2 == PLEIN)
        return a1;
    return kConsArbre(INTERIEUR, intersection(a1->fils[0], a2->fils[0]),
                                 intersection(a1->fils[1], a2->fils[1]),
                                 intersection(a1->fils[2], a2->fils[2]),
                                 intersection(a1->fils[3], a2->fils[3]),
                                 intersection(a1->fils[4], a2->fils[4]),
                                 intersection(a1->fils[5], a2->fils[5]),
                                 intersection(a1->fils[6], a2->fils[6]),
                                 intersection(a1->fils[7], a2->fils[7]));
}

float distancefi(Pointf a, Point b)
{
    return sqrtf( (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z));
}

float distancei(Point a, Point b)
{
    return sqrtf( (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z));
}

float distancef(Pointf a, Pointf b)
{
    return sqrtf( (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z));
}

void affiche_cube(int x1, int y1, int z1, int x2, int y2, int z2)
{
    glBegin(GL_QUADS);
        //Face dessous
        glVertex3f(x1, y1, z1);    
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);

        //Face dessus
        glVertex3f(x1, y2, z1);    
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        //Face devant
        glVertex3f(x1, y1, z1);    
        glVertex3f(x2, y1, z1);  
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);

        //Face derrière
        glVertex3f(x1, y1, z2);    
        glVertex3f(x2, y1, z2);  
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        //Face gauche
        glVertex3f(x1, y1, z1);    
        glVertex3f(x1, y2, z1);  
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y1, z2);    

        //Face droite
        glVertex3f(x2, y1, z1);    
        glVertex3f(x2, y2, z1);  
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);  
    glEnd();
}

void dessiner_plan1()
{
    glBegin(GL_QUADS);

        float x = -15;
        float y = 1;
        float z = -x;

        glColor3f(1.0,0.5,0.0); //Orange
        //Face dessous
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);
        glVertex3f(x, 0, z);
        glVertex3f(0, 0, z);

        //Face dessus
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);
        glVertex3f(x, 0, z);
        glVertex3f(0, 0, z);

        glColor3d(0.9,0.8,0.7); //Mur 1
        //Face devant
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);  
        glVertex3f(x, y, 0);
        glVertex3f(0, y, 0);

        glColor3d(0.9,0.8,0.5); //Mur 2
        //Face derrière
        glVertex3f(0, 0, z);    
        glVertex3f(x, 0, z);  
        glVertex3f(x, y, z);
        glVertex3f(0, y, z);

        glColor3d(0.9,0.8,0.7); //Mur 1
        //Face gauche
        glVertex3f(0, 0, 0);    
        glVertex3f(0, y, 0);  
        glVertex3f(0, y, z);
        glVertex3f(0, 0, z);    

        glColor3d(0.9,0.8,0.5); //Mur 2
        //Face droite
        glVertex3f(x, 0, 0);    
        glVertex3f(x, y, 0);  
        glVertex3f(x, y, z);
        glVertex3f(x, 0, z);  

    glEnd();

    //On remet la couleur blanche
    glColor4f(1.0,1.0,1.0,1.0);
    
}

void dessiner_maison()
{
    glBegin(GL_QUADS);

        float x = 5;
        float y = x;
        float z = x;

        glColor3f(1.0,0.5,0.0); //Orange
        //Face dessous
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);
        glVertex3f(x, 0, z);
        glVertex3f(0, 0, z);

        glColor3d(0.9,0.8,0.7); //Mur 1
        //Face devant
        glVertex3f(0, 0, 0);    
        glVertex3f(x, 0, 0);  
        glVertex3f(x, y, 0);
        glVertex3f(0, y, 0);

        glColor3d(0.9,0.8,0.5); //Mur 2
        //Face derrière
        glVertex3f(0, 0, z);    
        glVertex3f(x, 0, z);  
        glVertex3f(x, y, z);
        glVertex3f(0, y, z);

        glColor3d(0.9,0.8,0.7); //Mur 1
        //Face gauche
        glVertex3f(0, 0, 0);    
        glVertex3f(0, y, 0);  
        glVertex3f(0, y, z);
        glVertex3f(0, 0, z);    

        glColor3d(0.9,0.8,0.5); //Mur 2
        //Face droite
        glVertex3f(x, 0, 0);    
        glVertex3f(x, y, 0);  
        glVertex3f(x, y, z);
        glVertex3f(x, 0, z);  

    glEnd();

    glBegin(GL_QUADS);
        glColor3d(0.8,0,0); //Rouge un peu clair

        //Face dessus gauche
        glVertex3f(0, y, 0);   
        glVertex3f(0, y, z);
        glVertex3f(x/2, y+y/2, z);
        glVertex3f(x/2, y+y/2, 0);

        //Face dessus droite
        glVertex3f(x, y, 0);   
        glVertex3f(x, y, z);
        glVertex3f(x/2, y+y/2, z);
        glVertex3f(x/2, y+y/2, 0);

    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3d(0.8,0.1,0.1); //Rouge tuile
        //Face comblage avant
        glVertex3f(0, y, 0);   
        glVertex3f(x, y, 0);
        glVertex3f(x/2, y+y/2, 0);

        //Face comblage arrière
        glVertex3f(0, y, z);   
        glVertex3f(x, y, z);
        glVertex3f(x/2, y+y/2, z);
    glEnd();

    //On remet la couleur blanche
    glColor4f(1.0,1.0,1.0,1.0);
    
}

void affiche_boule(karbre arbre, Pointf p1, Pointf p2)
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    int z1 = p1.z;
    int z2 = p2.z;

	if (arbre->racine==PLEIN)
		affiche_cube(x1,y1,z1,x2,y2,z2);
	if (arbre->racine==RIEN)
	{
		affiche_boule(arbre->fils[0], creer_pointf(x1,y1, (z1+z2)/2),                creer_pointf((x1+x2)/2,(y1+y2)/2, z2));
		affiche_boule(arbre->fils[1], creer_pointf((x1+x2)/2, y1,(z1+z2)/2),         creer_pointf(x2,(y1+y2)/2, z2));
		affiche_boule(arbre->fils[2], creer_pointf((x1+x2)/2, y1,z1),                creer_pointf(x2, (y1+y2)/2,(z1+z2)/2));
		affiche_boule(arbre->fils[3], creer_pointf(x1,y1,z1),                        creer_pointf((x1+x2)/2,(y1+y2)/2, (z1+z2)/2));
		affiche_boule(arbre->fils[4], creer_pointf(x1,(y1+y2)/2, (z1+z2)/2),         creer_pointf((x1+x2)/2,y2, z2));
		affiche_boule(arbre->fils[5], creer_pointf((x1+x2)/2, (y1+y2)/2,(z1+z2)/2),  creer_pointf(x2,y2, z2));
		affiche_boule(arbre->fils[6], creer_pointf((x1+x2)/2, (y1+y2)/2,z1),         creer_pointf(x2,y2, (z1+z2)/2));
		affiche_boule(arbre->fils[7], creer_pointf(x1, (y1+y2)/2,z1),                creer_pointf((x1+x2)/2,y2, (z1+z2)/2));
	}
}