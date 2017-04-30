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

/*Permet d'afficher toutes les plateformes*/
void afficher_plateformes()
{
    int i;
    for (i=0; i<nb_plateformes; i++) //Parcourt toutes les plateformes 
    {
        //On récupère les coordonnées des 4 points qui définissent la plateforme
        int x1 = tab_plateformes[i].p1.x;
        int y1 = tab_plateformes[i].p1.y;
        int z1 = tab_plateformes[i].p1.z;

        int x2 = tab_plateformes[i].p2.x;
        int y2 = tab_plateformes[i].p2.y;
        int z2 = tab_plateformes[i].p2.z;

        int x3 = tab_plateformes[i].p3.x;
        int y3 = tab_plateformes[i].p3.y;
        int z3 = tab_plateformes[i].p3.z;

        int x4 = tab_plateformes[i].p4.x;
        int y4 = tab_plateformes[i].p4.y;
        int z4 = tab_plateformes[i].p4.z;


        glBegin(GL_QUADS);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        //Face dessus
        //glColor3f(0,0,1); //Bleu
        glTexCoord2i(0,0); glVertex3f(x1, y1, z1);    
        glTexCoord2i(0,2); glVertex3f(x2, y2, z2);    
        glColor3f(0,0.5,0.5); //Vert
        glTexCoord2i(2,2); glVertex3f(x3, y3, z3);
        glTexCoord2i(2,0); glVertex3f(x4, y4, z4);

        glColor3f(1,1,1);  //Blanc

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

        glColor3f(0,0,1); //Bleu        

        //Face du dessous 
        glVertex3f(x1, y1-2, z1);    
        glVertex3f(x2, y2-2, z2);
        glVertex3f(x3, y3-2, z3);
        glVertex3f(x4, y4-2, z4);

        glColor3f(1,1,1); //Blanc   

        glEnd();
    }
}

float rand_0_1()
{
   return (float)rand() / (float)RAND_MAX;
}

void afficher_decor()
{
    int x1 = -500;
    int y1 = -101;
    int z1 = -500;
    int x2 = 500;
    int y2 = -101;
    int z2 = 500;

    glBegin(GL_QUADS);
    
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    //Face dessus
        glColor3f(0,0,1); //Bleu
        /*glTexCoord2i(0,0);*/ glVertex3f(x1, y1, z1);    
        /*glTexCoord2i(0,1);*/ glVertex3f(x2, y1, z1);    
        glColor3f(0,0.5,0.5); //Bleu clair    
        /*glTexCoord2i(1,1);*/ glVertex3f(x2, y2, z2);
        /*glTexCoord2i(1,0);*/ glVertex3f(x1, y2, z2);

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

void definir_decor(int nombre)
{
    int largeur_element = 50;
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