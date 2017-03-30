#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

void definir_polygone_affiche(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
    //printf("x0=%d",x0);
    nombre_sommets = 4;
    sommet = malloc(sizeof(Point)*nombre_sommets);
    sommet[0].x = x0;   sommet[0].y = y0;   sommet[0].z = 1;
    sommet[1].x = x1;   sommet[1].y = y1;   sommet[1].z = 1;
    sommet[2].x = x2;   sommet[2].y = y2;   sommet[2].z = 1;
    sommet[3].x = x3;   sommet[3].y = y3;   sommet[3].z = 1;

    // printf("sommet:(%d,%d) (%d,%d) (%d,%d) (%d,%d)",sommet[0].x,sommet[0].y,sommet[1].x,sommet[1].y,sommet[2].x,sommet[2].y,sommet[3].x,sommet[3].y);
        
    init_lct();
    remplissage();
    balayage();
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
}

void definir_polygone_affiche_point(Point p1, Point p2, Point p3, Point p4)
{
    nombre_sommets = 4;
    sommet = malloc(sizeof(Point)*nombre_sommets);
    sommet[0].x = p1.x;   sommet[0].y = p1.y;   sommet[0].z = 1;
    sommet[1].x = p2.x;   sommet[1].y = p2.y;   sommet[1].z = 1;
    sommet[2].x = p3.x;   sommet[2].y = p3.y;   sommet[2].z = 1;
    sommet[3].x = p4.x;   sommet[3].y = p4.y;   sommet[3].z = 1;

    // printf("sommet:(%d,%d) (%d,%d) (%d,%d) (%d,%d)",sommet[0].x,sommet[0].y,sommet[1].x,sommet[1].y,sommet[2].x,sommet[2].y,sommet[3].x,sommet[3].y);

    init_lct();
    remplissage();
    balayage();
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
}

//Fonction de tracage d'un point de côte 2n
void trace_point(int x, int y, int n)
{
    glBegin(GL_QUADS);
        x*=n;
        y*=n;
        glVertex2i(x-n, y-n);
        glVertex2i(x, y-n);
        glVertex2i(x, y);
        glVertex2i(x-n, y);
    glEnd();
}

//Tracage de la grille des points
void trace_grille(int n)
{
    glColor3f(1.0,1.0,1.0); //Blanc
    
    // glBegin(GL_LINES);
    // for(int i=-TAILLE; i<=TAILLE; i+=n)
    // {
    //     glVertex2i(-TAILLE, i);
    //     glVertex2i(TAILLE, i);
    //     glVertex2i(i, TAILLE);
    //     glVertex2i(i, -TAILLE);
        
    // }
    // glEnd();

    glColor3f(1.0,0.0,0.0); //Rouge

    glBegin(GL_LINES);  //X
        glVertex3i(-TAILLE,0,0);
        glVertex3i(TAILLE,0,0);
    glEnd();

    glBegin(GL_LINES); //Y
        glVertex3i(0,-TAILLE,0);
        glVertex3i(0,TAILLE,0);
    glEnd();

    glBegin(GL_LINES); //Z
        glVertex3i(0,0,-TAILLE);
        glVertex3i(0,0,TAILLE);
    glEnd();

    glFlush();

    glColor3f(1.0,1.0,1.0); //Blanc
}

//Retourne le plus grand entre a et b
float max(float a, float b)
{
    return (a>b)?a:b;
}

//Retourne le plus grand entre a et b
float min(float a, float b)
{
    return (a<b)?a:b;
}

//Trace le segment entre x1 et x2
void segment(int x1, int x2, int y) 
{
    int i;
    if(x1<x2)
    {
        for(i=x1; i<=x2; i++)
        {
            trace_point(i, y, 1);
        }
    }
    else
    {
        for(i=x2; i<=x1; i++)
        {
            trace_point(i, y, 1);
        }
    }
}

//Lance le remplissage de LC LCS LCE
void remplissage()
{
    lc = malloc((2*nombre_sommets)*sizeof(Cote));

    //On recupère tous les côtes, on rempli les x/y min/max
    get_lc();

    trier_lce(); //lce sera accessible avec lc[e[i]];
    trier_lcs(); //lcs sera accessible avec lc[s[i]];
}

//Récupère la liste de côté et la stock dans LC
void get_lc()
{
    int i;
    for(i=0; i<nombre_sommets-1; i++)
    {
        lc[i].pointA.x = sommet[i].x;
        lc[i].pointA.y = sommet[i].y;
        lc[i].pointB.x = sommet[i+1].x;
        lc[i].pointB.y = sommet[i+1].y;

        if(lc[i].pointA.x < lc[i].pointB.x)
        {
            lc[i].xmin = lc[i].pointA.x;
            lc[i].xmax = lc[i].pointB.x;
        }
        else
        {
            lc[i].xmin = lc[i].pointB.x;
            lc[i].xmax = lc[i].pointA.x;
        }
        if(lc[i].pointA.y < lc[i].pointB.y)
        {
            lc[i].ymin = lc[i].pointA.y;
            lc[i].ymax = lc[i].pointB.y;
        }
        else
        {
            lc[i].ymin = lc[i].pointB.y;
            lc[i].ymax = lc[i].pointA.y;
        }
    }

    //Pour le dernier côté

    lc[nombre_sommets-1].pointA.x = sommet[nombre_sommets-1].x;
    lc[nombre_sommets-1].pointA.y = sommet[nombre_sommets-1].y;
    lc[nombre_sommets-1].pointB.x = sommet[0].x;
    lc[nombre_sommets-1].pointB.y = sommet[0].y;

    if(lc[nombre_sommets-1].pointA.x < lc[nombre_sommets-1].pointB.x)
    {
        lc[nombre_sommets-1].xmin = lc[nombre_sommets-1].pointA.x;
        lc[nombre_sommets-1].xmax = lc[nombre_sommets-1].pointB.x;
    }
    else
    {
        lc[nombre_sommets-1].xmin = lc[nombre_sommets-1].pointB.x;
        lc[nombre_sommets-1].xmax = lc[nombre_sommets-1].pointA.x;
    }
    if(lc[nombre_sommets-1].pointA.y < lc[nombre_sommets-1].pointB.y)
    {
        lc[nombre_sommets-1].ymin = lc[nombre_sommets-1].pointA.y;
        lc[nombre_sommets-1].ymax = lc[nombre_sommets-1].pointB.y;
    }
    else
    {
        lc[nombre_sommets-1].ymin = lc[nombre_sommets-1].pointB.y;
        lc[nombre_sommets-1].ymax = lc[nombre_sommets-1].pointA.y;
    }
}

//Tri LCE
void trier_lce()
{
    //Tableau des rangs qui va servir à faire les echanges jusqu'à qu'on ai trouvé les valeurs triés
    //C'est un test, peut-être est-ce mieux niveau complexite?
    e = malloc(sizeof(int)*nombre_sommets);
    int i;
    for(i=0; i<nombre_sommets; i++)
    {
        e[i]=i;
    }

    int trie = 0;

    while(!trie)
    {
        //Le tableau sera trie si cette valeur n'est pas modifie
        trie = 1;

        for(i=1; i<nombre_sommets; i++)
        {
            //On a trouve 2 valeurs qui ne sont pas tries
            if(lc[e[i-1]].ymin > lc[e[i]].ymin)
            {
                trie = 0;
                //On echange ces 2 valeurs dans rang
                e[i] = e[i-1] + e[i];
                e[i-1] = e[i] - e[i-1];
                e[i] = e[i] - e[i-1];
            }
        }

            // printf("Rang: ");
            // for(i=0; i<nombre_sommets; i++)
            // {
            //     printf("%d ", e[i]);
            // }
            // printf("\n");
    }
}

//Tri LCS
void trier_lcs()
{
    s = malloc(sizeof(int)*nombre_sommets);
    int i;

    //On initialise le tableau s
    for(i=0; i<nombre_sommets; i++)
    {
        s[i]=i;
    }

    int trie = 0;
    while(!trie)
    {
        //Le tableau sera trie si cette valeur n'est pas modifie
        trie = 1;

        for(i=1; i<nombre_sommets; i++)
        {
            //On a trouve 2 valeurs qui ne sont pas tries
            if(lc[s[i-1]].ymax > lc[s[i]].ymax)
            {
                trie = 0;
                //On echange ces 2 valeurs dans rang
                s[i] = s[i-1] + s[i];
                s[i-1] = s[i] - s[i-1];
                s[i] = s[i] - s[i-1];
            }
        }
    }
}

//Test l'appartenance à un côté d'un point
int appartient_cote(int numero_cote, int xa, int ya)
{
    //On élimine le cas où le point est sur la droite mais en dehors du segment

    if(lc[numero_cote].xmin > xa || lc[numero_cote].xmax < xa)
        return 0;
    if(lc[numero_cote].ymin > ya || lc[numero_cote].ymax < ya)
        return 0;

    //On teste si le point est sur la droite

    double coef_dir = (lc[numero_cote].pointB.y-lc[numero_cote].pointA.y)/(lc[numero_cote].pointB.x-lc[numero_cote].pointA.x);
    double ordonnee_origine = lc[numero_cote].pointA.y-coef_dir*lc[numero_cote].pointA.x;

    // printf("m=%f & oo=%f\n",coef_dir, ordonnee_origine);

    // printf("calcul:%f & ya=%d\n", coef_dir*xa+ordonnee_origine, ya);
    return (coef_dir*xa+ordonnee_origine==ya);
}

//Initialise LCT
void init_lct()
{
    t = malloc(sizeof(int)*nombre_sommets*nombre_sommets);
    next_lct = 0;
}

//Ajouter un côté dans LCT
void ajout_lct(int num_cote)
{
     
    if(next_lct!=0) //LCT non vide
    {
        int i, j;
       
        for(i=0; i<next_lct; i++)
        {
            if(lc[t[i]].xmin>lc[num_cote].xmin) //On recherche la bonne place pour l'ajout
            {
                for(j=next_lct; j>i; j--) //On décale après la position pour insérer
                {
                    // printf("t[j] = t[j-1] <=> t[%d] = t[%d] <=> t[%d] = %d\n",j,j-1,j,t[j-1]);
                    t[j] = t[j-1];
                    // printf("next_lct=%d et j=%d et j-1=%d et i=%d\n",next_lct,j,j-1,i);
                    // printf("for(j=next_lct; j>i; j--) <=> j (%d) -> i (%d)\n",j,i);
                }
                t[i] = num_cote;
                next_lct++;
                return ;
            }
        }
        
        t[next_lct] = num_cote; //On l'insère
    }
    else    //LCT vide
    {
        t[0] = num_cote;
    }
    
    next_lct++;
}   
    
//Supprime un côté de LCT
void suppression_lct(int num_cote)
{
    //printf("\nnext_lct=%d\n",next_lct);
    if(num_cote == t[next_lct-1])    //Dernier de LCT
    {
        t[next_lct-1]=-1;
        next_lct--;
    }
    else    //Sinon on décale
    {
        int i, j;
        for(i=0; i<next_lct; i++)
        {
            if(t[i]==num_cote)  //On l'a trouvé dans LCT
            {
                for(j=i; j<next_lct; j++)
                {
                    t[j]=t[j+1];
                }
                next_lct--;
                break;
            }
        }
        if(i==next_lct)
        {
            printf("Erreur: on a pas trouvé coté num %d dans LCT\n",num_cote);
        }
    }
}

//On cherche le ymin le plus petit
int balayage_limite_basse()
{
    int i, ymin=TAILLE;
    for(i=0; i<nombre_sommets; i++)
    {
        if(lc[i].ymin < ymin)
        {
            ymin = lc[i].ymin;
        }
    }
    return ymin;
}

//On cherche le ymin le plus grand
int balayage_limite_haute()
{
        int i, ymax=-TAILLE;
        for(i=0; i<nombre_sommets; i++)
        {
            if(lc[i].ymax > ymax)
            {
                ymax = lc[i].ymax;
            }
            //printf("lc[%d].ymax = %d\n",i,lc[i].ymax);
        } 
    return ymax;
}

//Teste si un côté à un coef directeur nul
int coef_dir_nul(int numero_cote)
{   
    return (lc[numero_cote].pointB.y-lc[numero_cote].pointA.y)/(lc[numero_cote].pointB.x-lc[numero_cote].pointA.x == 0);
}   
    
//Donne le X du point d'intersection avec un coté au niveau Y
float interection_y_cote(int numero_cote, int y)  //Renvoi le x
{   
    double xa=lc[numero_cote].pointA.x;
    double ya=lc[numero_cote].pointA.y;
    double xb=lc[numero_cote].pointB.x;
    double yb=lc[numero_cote].pointB.y;

    if(ya==yb)
    {
        return ya;
    }
    if(xb-xa==0)
    {
        return xa;
    }

    // printf("\tCalcul de l'intersection avec %d\n"/*: Yb-Ya/Xb-Xa = %f-%f/%f-%f\n"*/, numero_cote/*,yb,ya,xb,xa*/);
    
    double coef_dir = (yb-ya)/(xb-xa);
    double ordonnee_origine = ya-(coef_dir*xa);

    if(coef_dir != 0)   //On évite la division par 0
    {
        return (y-ordonnee_origine)/(coef_dir);
    }

    return xa;
}

//Fonction principale du balayage pour le remplissage
void balayage()
{
    //On trouve l'intervalle des y à balayer
        int i;
        int ymin = balayage_limite_basse();
        int ymax = balayage_limite_haute();

        // printf("sommet:(%d,%d) (%d,%d) (%d,%d) (%d,%d)",sommet[0].x,sommet[0].y,sommet[1].x,sommet[1].y,sommet[2].x,sommet[2].y,sommet[3].x,sommet[3].y);
        // printf("\nymin=%d ymax=%d",ymin,ymax);

    //Balayage
        int rangLCS=0;
        int rangLCE=0;

        for(i=ymin; i<=ymax; i++)   //On est à la couche y=i
        {
            // printf("Couche y=%d (sur %d)\n",i,ymax);
            if(i!=ymax)
            {
                while(i==lc[e[rangLCE]].ymin && rangLCE<nombre_sommets) //Côté(s) entrant(s)
                {
                    // printf("\tAjouté LCT: (%d,%d)(%d,%d)\n",lc[e[rangLCE]].pointA.x,lc[e[rangLCE]].pointA.y,lc[e[rangLCE]].pointB.x,lc[e[rangLCE]].pointB.y);
                    // printf("rangLCE=%d nombre_sommets=%d\n",rangLCE,nombre_sommets);
                    ajout_lct(e[rangLCE]);
                    
                    if(rangLCE<nombre_sommets)  //Si on a pas traité tout LCE
                        rangLCE++;  //On incrémente le rang où on regarde dans LCE (car traité)
                }
                while(i==lc[s[rangLCS]].ymax && rangLCS<nombre_sommets) //Côté(s) sortant(s)
                {
                    // printf("\tSupprimé LCT: (%d,%d)(%d,%d)\n",lc[s[rangLCS]].pointA.x,lc[s[rangLCS]].pointA.y,lc[s[rangLCS]].pointB.x,lc[s[rangLCS]].pointB.y);
                    suppression_lct(s[rangLCS]);
                    if(rangLCS<nombre_sommets) //Si on a pas traité tout LCS
                        rangLCS++;  //On incrémente le rang où on regarde dans LCS (car traité)
                }
            }  

            //On calcule l'intersection de notre y avec chaque côté de LCT

                // printf("\tNombre LCT=%d\n", next_lct);

                int j;
                float *x_intersect = malloc(sizeof(float)*next_lct);    
                for(j=0; j<next_lct; j++)
                {
                    x_intersect[j] = interection_y_cote(t[j], i);
                    // printf("\t\tx(LCT%d)=%f & Cote=(%d,%d)(%d,%d)\n", j, x_intersect[j], lc[t[j]].pointA.x, lc[t[j]].pointA.y, lc[t[j]].pointB.x, lc[t[j]].pointB.y);
                }

            //Affichage de la ligne


                if(next_lct>0) //Si il y a des LCT
                {
                    if(next_lct%2==0)//Si il y a un nombre pair de LCT
                    {
                        int k;
                        for(k=0; k<next_lct-1; k+=2)
                        {
                            segment(x_intersect[k], x_intersect[k+1], i);
                        }
                    }
                    else
                    {
                        printf("Problème avec le polygone (%d côtés à la fois)\n",next_lct);
                        exit(-1);
                    }
                }

        }
}