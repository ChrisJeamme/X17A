#include "decor.h"

/*Permet de dessiner la boule avec un rayon donné et les coordonnées du centre*/
void dessiner_boule(float rayon, float x, float y, float z)
{
    glBindTexture(GL_TEXTURE_2D, tex_sol[1]);
    glColor3f(1,0,0);   //Rouge 
    glTranslatef(x, y, z);
    glutSolidSphere(rayon, 20, 20);
    glTranslatef(-x, -y, -z);
    glColor3f(1,1,1);   //Blanc
    glBindTexture(GL_TEXTURE_2D, tex_sol[0]);
}

/*Permet de cherger une texture*/
void chargementTexture(GLuint* texture, char* chemin)
{
    *texture = SOIL_load_OGL_texture(chemin,
                                     SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID,
                                     SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
                                    );
    if(texture==NULL)
        fprintf(stderr,"Erreur de chargement de texture: \"%s\"\n", chemin);
}

void chargerTextureCubemap(GLuint* texture, char *x_pos_file, char *x_neg_file, char *y_pos_file, char *y_neg_file, char *z_pos_file, char *z_neg_file)
{
    *texture = SOIL_load_OGL_cubemap(x_pos_file,
                                     x_neg_file,
                                     y_pos_file,
                                     y_neg_file,
                                     z_pos_file,
                                     z_neg_file,
                                     SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID,
                                     SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
                                    );
    if(texture==NULL)
        fprintf(stderr,"Erreur de chargement de texture\n");
}

void afficher_la_plateforme(plateforme p)
{
//On récupère les coordonnées des 4 points qui définissent la plateforme
    int x1 = p.p1.x;
    int y1 = p.p1.y;
    int z1 = p.p1.z;

    int x2 = p.p2.x;
    int y2 = p.p2.y;
    int z2 = p.p2.z;

    int x3 = p.p3.x;
    int y3 = p.p3.y;
    int z3 = p.p3.z;

    int x4 = p.p4.x;
    int y4 = p.p4.y;
    int z4 = p.p4.z;


    glBegin(GL_QUADS);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    int distancex = ((x1>=x3)?x1-x3:x3-x1);
    int distancez = ((z1>=z3)?z1-z3:z3-z1);

    if(distancex==0)
        distancex=1;
    if(distancez==0)
        distancez=1;

    //Face dessus
    glColor3f(0.7,0,0); 
    glTexCoord2i(0,0); glVertex3f(x1, y1, z1);    
    glTexCoord2i(0,distancez/10); glVertex3f(x2, y2, z2);    
    glColor3f(0.4,0,0); 
    glTexCoord2i(distancex/10,distancez/10); glVertex3f(x3, y3, z3);
    glTexCoord2i(distancex/10,0); glVertex3f(x4, y4, z4);

    glColor3f(0.1,0,0);  //Blanc

    //Bord 1
    glVertex3f(x1, y1, z1);    
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2-2, z2);
    glVertex3f(x1, y1-2, z1);

    //Bord 2
    glVertex3f(x2, y2, z2);    
    glVertex3f(x3, y3, z3);
    glVertex3f(x3, y3-2, z3);
    glVertex3f(x2, y2-2, z2);

    //Bord 3
    glVertex3f(x3, y3, z3);    
    glVertex3f(x4, y4, z4);
    glVertex3f(x4, y4-2, z4);
    glVertex3f(x3, y3-2, z3);

    //Bord 4
    glVertex3f(x4, y4, z4);    
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1-2, z1);
    glVertex3f(x4, y4-2, z4);

    glColor3f(0,0,0); //Noir      

    //Face du dessous 
    glVertex3f(x1, y1-2, z1);    
    glVertex3f(x2, y2-2, z2);
    glVertex3f(x3, y3-2, z3);
    glVertex3f(x4, y4-2, z4);

    glColor3f(1,1,1); //Blanc   

    glEnd();
}


/*Permet d'afficher toutes les plateformes*/
void afficher_plateformes()
{
    int i;
    for (i=0; i<nb_plateformes; i++) //Parcourt toutes les plateformes 
    {
        afficher_la_plateforme(tab_plateformes[i]);
    }
    for (i=0; i<nb_sauts; i++)
    {
        afficher_la_plateforme(tab_sauts[i]);
    }
}

void afficher_objets()
{
    int i;
    for (i=0; i<nb_objets; i++)
    {
        int x1 = tab_objets[i].p1.x;
        int x2 = tab_objets[i].p2.x;
        int y1 = tab_objets[i].p1.y;
        int y2 = tab_objets[i].p2.y;
        int z1 = tab_objets[i].p1.z;
        int z2 = tab_objets[i].p2.z;
        parallelepipede(x1,y1,z1, x2,y2,z2);
    }
}

float rand_0_1()
{
   return (float)rand() / (float)RAND_MAX;
}

void afficher_decor()
{
    glBegin(GL_QUADS);

    glColor3f(1,1,1); //Blanc   


    int i;
    for(i=0; i<nb_element_decor; i++)
    {
        int x1 = tab_decor[i].p1.x;
        int y1 = tab_decor[i].p1.y;
        int z1 = tab_decor[i].p1.z;
        int x2 = tab_decor[i].p3.x;
        int y2 = tab_decor[i].p3.y;
        int z2 = tab_decor[i].p3.z;
        couleur couleur_cotes = tab_decor[i].couleur_cotes;
        couleur couleur_dessus = tab_decor[i].couleur_dessus;
        

        //Face dessus
            glColor3f(couleur_dessus.r,couleur_dessus.v,couleur_dessus.b);
                glVertex3f(x1, y1, z1);    
                glVertex3f(x2, y1, z1);    
                glVertex3f(x2, y2, z2);
                glVertex3f(x1, y2, z2);

        //Faces côtés
            glColor3f(couleur_cotes.r,couleur_cotes.v,couleur_cotes.b);
                glVertex3f(x1, y1, z1);    
                glVertex3f(x2, y1, z1); 
                glVertex3f(x2, -100, z1);
                glVertex3f(x1, -100, z1);    
            glColor3f(couleur_cotes.r,couleur_cotes.v,couleur_cotes.b);
                glVertex3f(x2, y1, z1);    
                glVertex3f(x2, y2, z2);    
                glVertex3f(x2, -100, z2);
                glVertex3f(x2, -100, z1);  
            glColor3f(couleur_cotes.r,couleur_cotes.v,couleur_cotes.b);
                glVertex3f(x2, y2, z2);
                glVertex3f(x1, y2, z2);
                glVertex3f(x1, -100, z2);
                glVertex3f(x2, -100, z2);
            glColor3f(couleur_cotes.r,couleur_cotes.v,couleur_cotes.b);
                glVertex3f(x1, y2, z2);
                glVertex3f(x1, y1, z1);
                glVertex3f(x1, -100, z1);
                glVertex3f(x1, -100, z2);

        glColor3f(1,1,1); //Blanc   
       
    }
    glEnd();
}

void afficher_cubemap()
{
    int t = 700;

    glBindTexture(GL_TEXTURE_2D, tex_skybox[0]);
    glBegin(GL_QUADS);			// X Négatif		
        glTexCoord2i(0,0); glVertex3f(-t,-t,-t); 	
        glTexCoord2i(0,1); glVertex3f(-t,t,-t);
        glTexCoord2i(1,1); glVertex3f(-t,t,t);
        glTexCoord2i(1,0); glVertex3f(-t,-t,t);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, tex_skybox[1]);
    glBegin(GL_QUADS);			// X Positif
        glTexCoord2i(0,0);  glVertex3f(t,-t,-t);
        glTexCoord2i(0,1);  glVertex3f(t,t,-t);
        glTexCoord2i(1,1);  glVertex3f(t,t,t); 
        glTexCoord2i(1,0);  glVertex3f(t,-t,t); 	
    glEnd();
    
    // glBindTexture(GL_TEXTURE_2D, tex_skybox[2]);
    // glBegin(GL_QUADS);			// Y Négatif	
    //     glTexCoord2i(0,0); glVertex3f(-t,-t,-t);
    //     glTexCoord2i(0,1); glVertex3f(-t,-t,t);
    //     glTexCoord2i(1,1); glVertex3f(t,-t,-t);
    //     glTexCoord2i(1,0); glVertex3f(t,-t,t);
    // glEnd();
    
    glBindTexture(GL_TEXTURE_2D, tex_skybox[3]);
    glBegin(GL_QUADS);			// Y Positif		
        glTexCoord2i(0,0); glVertex3f(-t,t,-t);
        glTexCoord2i(0,1); glVertex3f(t,t,-t); 
        glTexCoord2i(1,1); glVertex3f(t,t,t);
        glTexCoord2i(1,0); glVertex3f(-t,t,t); 	
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, tex_skybox[4]);
    glBegin(GL_QUADS);			// Z Négatif		
        glTexCoord2i(0,0);  glVertex3f(-t,-t,-t);
        glTexCoord2i(0,1);  glVertex3f(-t,t,-t);
        glTexCoord2i(1,1);  glVertex3f(t,t,-t);
        glTexCoord2i(1,0);  glVertex3f(t,-t,-t); 
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, tex_skybox[5]);
    glBegin(GL_QUADS);			// Z Positif	
        glTexCoord2i(0,0);  glVertex3f(-t,-t,t);
        glTexCoord2i(0,1);  glVertex3f(-t,t,t);
        glTexCoord2i(1,1);  glVertex3f(t,t,t);
        glTexCoord2i(1,0);  glVertex3f(t,-t,t); 
    glEnd();
}

void definir_decor(int largeur_element)
{
    int i, j;
    for(i=-500; i<=500-largeur_element; i+=largeur_element) 
    {
        for(j=-500; j<=500-largeur_element; j+=largeur_element)
        {
            int hauteur = -100+abs(rand()*2*largeur_element%largeur_element);
            
            ajouter_element_decor(
                nouveau_point(i,hauteur,j),
                nouveau_point(i+largeur_element,hauteur,j),
                nouveau_point(i+largeur_element,hauteur,j+largeur_element),
                nouveau_point(i,hauteur,j+largeur_element)
            );
        }
    }
}

/*Permet de creer un point avec 3 coordonnées*/
point nouveau_point(int x, int y, int z)
{
    point p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

/*Permet de creer une couleur avec 3 float*/
couleur nouvelle_couleur(float r, float v, float b)
{
    couleur c;
    c.r=r;
    c.v=v;
    c.b=b;
    return c;
}

/*Ajoute une plate-forme grace a 4 points*/
void ajouter_plateforme(point p1, point p2, point p3, point p4)
{
    plateforme p;
    p.p1 = p1;
    p.p2 = p2;
    p.p3 = p3;
    p.p4 = p4;
    tab_plateformes[nb_plateformes++] = p;
}

/*Ajoute une plateforme de saut*/
void ajouter_saut(point p1, point p2, point p3, point p4)
{
    plateforme p;
    p.p1 = p1;
    p.p2 = p2;
    p.p3 = p3;
    p.p4 = p4;
    tab_sauts[nb_sauts++] = p;
}

/*Ajoute un objet dans le monde*/
void ajouter_objet(point p1, point p2)
{
    objet o;
    o.p1 = p1;
    o.p2 = p2;
    
    //Random sur le vert
    float r = 0;
    float v = rand_0_1();
    float b = 0;

    o.coul = nouvelle_couleur(r,v,b);

    tab_objets[nb_objets++] = o;
}

/*Ajoute une plate-forme qui existe déjà au niveau*/
void ajouter_plateforme_charge(plateforme p)
{
    tab_plateformes[nb_plateformes++] = p;
}

/*Ajoute une plate-forme de saut qui existe déjà au niveau*/
void ajouter_saut_charge(plateforme p)
{
    tab_sauts[nb_sauts++] = p;
}

void ajouter_element_decor(point p1, point p2, point p3, point p4)
{
    element_decor p;
    p.p1 = p1;
    p.p2 = p2;
    p.p3 = p3;
    p.p4 = p4;

    float r;
    float v;
    float b;

    //Random sur le vert
    r = 0;
    v = rand_0_1();
    b = 0;

    float r2 = (r-0.1)>0?r-0.1:0;
    float v2 = (v-0.1)>0?v-0.1:0;
    float b2 = (b-0.1)>0?b-0.1:0;

    p.couleur_cotes = nouvelle_couleur(r,v,b);
    p.couleur_dessus = nouvelle_couleur(r2,v2,b2);
    tab_decor[nb_element_decor++] = p;
}

/*Tracage de la grille des points*/
void trace_grille(int n)
{
    glColor3f(1.0,1.0,1.0); //Blanc
    
    //Afficher X et Y sur le repère
        // afficherText(10,0,0,1,1,"X");
        // afficherText(0,10,0,1,1,"Y");
        // afficherText(-10,0,0,1,1,"X");
        // afficherText(0,-10,0,1,1,"Y");
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

void afficherText(float x, float y, int r, int g, int b, const char *texte) 
{
	int i, j = strlen(texte);
	glColor3f(r,g,b);
	glRasterPos2f(x,y);
	for(i=0; i<j; i++)
    {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, texte[i] );
	}
    glColor3f(1,1,1);
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


void parallelepipede(int x1, int y1, int z1, int x2, int y2, int z2)
{
    glColor3f(1,1,1); //Blanc   
    
        glBegin(GL_QUADS);

        //Face 1
        glVertex3f(x1, y1, z1);    
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y1, z1);

        //Bord 2
        glVertex3f(x1, y1, z1);    
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);

        //Bord 3
        glVertex3f(x1, y1, z1);    
        glVertex3f(x1, y1, z2);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y2, z1);

        //Face 4
        glVertex3f(x1, y1, z2);    
        glVertex3f(x1, y2, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);

        //Bord 5
        glVertex3f(x1, y2, z1);    
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        //Bord 6
        glVertex3f(x2, y1, z1);    
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y2, z1);
 

        glEnd();
}


//On fournit un point (l'arrivée) et un caractère (x ou z) pour l'orientation
void portail(point p, char orientation)
{
    int x1 = p.x;
    int y = p.y;
    int z1 = p.z;

    float base1x, base1z, base2x, base2z;
    if (orientation == 'x')
    {    
        base1x = x1-5;
        base1z = z1;
        base2x = x1+5;
        base2z = z1;
    }
    else
    {
        base1x = x1;
        base1z = z1-5;
        base2x = x1;
        base2z = z1+5;
    }

    glColor3f(1,1,1); //Blanc   

    ajouter_objet(nouveau_point(base1x-1, y, base1z-1), nouveau_point(base1x+1,y+8,base1z+1));
    //parallelepipede(base1x-1, y, base1z-1, base1x+1,y+8,base1z+1);
    //Deuxième pilier
    ajouter_objet(nouveau_point(base2x-1, y, base2z-1), nouveau_point(base2x+1,y+8,base2z+1));
    //parallelepipede(base2x-1, y, base2z-1, base2x+1,y+8,base2z+1);
    //Partie supérieure
    parallelepipede(base1x-1, y+8, base1z-1, base2x+1,y+10,base2z+1);
    
    glColor3f(0,1,1); //Cyan       
    //Enfin, la partie centrale où il faudra appliquer la texture
    glBegin(GL_QUADS);
        glVertex3f(base1x, y, base1z);    
        glVertex3f(base1x, y+9, base1z);
        glVertex3f(base2x, y+9, base2z);
        glVertex3f(base2x, y, base2z);
    glEnd();

    glColor3f(1,1,1); //Blanc   

}

void generer_objet_sur_plateforme(plateforme p)
{
    //On recupère les limites de la plateforme 
    int xmin = min(p.p1.x, p.p2.x, p.p3.x);
    int xmax = max(p.p1.x, p.p2.x, p.p3.x)-5;
    int zmin = min(p.p1.z, p.p2.z, p.p3.z);
    int zmax = max(p.p1.z, p.p2.z, p.p3.z)-5;
    int y = p.p1.y;

    int x1 = rand()%(xmax-xmin) +xmin;
    int z1 = rand()%(zmax-zmin) +zmin;

    int dx = rand()%(5)+1;
    int dz = rand()%(5)+1;
    int dy = rand()%(3)+4;

    ajouter_objet(nouveau_point(x1,y,z),nouveau_point(x1+dx, y+dy, z1+dz));

}

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

// void afficher_cubemap()
// {
//     int t = 500;
//     int n = 1;

//     glBindTexture(GL_TEXTURE_2D, tex_skybox[0]);
//     glBegin(GL_TRIANGLE_STRIP);			// X Négatif		
//         glTexCoord3f(-n,-n,-n); glVertex3f(-t,-t,-t); 	
//         glTexCoord3f(-n,n,-n); glVertex3f(-t,t,-t);
//         glTexCoord3f(-n,-n,n); glVertex3f(-t,-t,t);
//         glTexCoord3f(-n,n,n); glVertex3f(-t,t,t);
//     glEnd();
    
//     glBindTexture(GL_TEXTURE_2D, tex_skybox[1]);
//     glBegin(GL_TRIANGLE_STRIP);			// X Positif
//         glTexCoord3f(n, -n,-n); glVertex3f(t,-t,-t);
//         glTexCoord3f(n,-n,n); glVertex3f(t,-t,t);
//         glTexCoord3f(n,n,-n); glVertex3f(t,t,-t); 
//         glTexCoord3f(n,n,n); glVertex3f(t,t,t); 	
//     glEnd();
    
//     glBindTexture(GL_TEXTURE_2D, tex_skybox[2]);
//     glBegin(GL_TRIANGLE_STRIP);			// Y Négatif	
//         glTexCoord3f(-n,-n,-n); glVertex3f(-t,-t,-t);
//         glTexCoord3f(-n,-n,n); glVertex3f(-t,-t,t);
//         glTexCoord3f(n, -n,-n); glVertex3f(t,-t,-t);
//         glTexCoord3f(n,-n,n); glVertex3f(t,-t,t);
//     glEnd();
    
//     glBindTexture(GL_TEXTURE_2D, tex_skybox[3]);
//     glBegin(GL_TRIANGLE_STRIP);			// Y Positif		
//         glTexCoord3f(-n,n,-n); glVertex3f(-t,t,-t);
//         glTexCoord3f(n,n,-n); glVertex3f(t,t,-t); 
//         glTexCoord3f(-n,n,n); glVertex3f(-t,t,t);
//         glTexCoord3f(n,n,n); glVertex3f(t,t,t); 	
//     glEnd();
    
//     glBindTexture(GL_TEXTURE_2D, tex_skybox[4]);
//     glBegin(GL_TRIANGLE_STRIP);			// Z Négatif		
//         glTexCoord3f(-n,-n,-n); glVertex3f(-t,-t,-t);
//         glTexCoord3f(n, -n,-n); glVertex3f(t,-t,-t);
//         glTexCoord3f(-n,n,-n); glVertex3f(-t,t,-t);
//         glTexCoord3f(n,n,-n); glVertex3f(t,t,-t); 
//     glEnd();
    
//     glBindTexture(GL_TEXTURE_2D, tex_skybox[5]);
//     glBegin(GL_TRIANGLE_STRIP);			// Z Positif	
//         glTexCoord3f(-n,-n,n); glVertex3f(-t,-t,t);
//         glTexCoord3f(-n,n,n); glVertex3f(-t,t,t);
//         glTexCoord3f(n,-n,n); glVertex3f(t,-t,t);
//         glTexCoord3f(n,n,n); glVertex3f(t,t,t); 	
//     glEnd();
//     glDepthMask(GL_TRUE);
// }