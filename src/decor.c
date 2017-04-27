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
                                     SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT
                                    );
    if(texture==NULL)
        fprintf(stderr,"Erreur de chargement de texture: \"%s\"\n", chemin);
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
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        //Face dessus
        //glColor3f(0,0,1); //Bleu
        glTexCoord2i(0,0); glVertex3f(x1, y1, z1);    
        glTexCoord2i(0,1); glVertex3f(x2, y2, z2);    
        glColor3f(0,0.5,0.5); //Vert      
        glTexCoord2i(1,1); glVertex3f(x3, y3, z3);
        glTexCoord2i(1,0); glVertex3f(x4, y4, z4);


        //Bord 1
        glColor3f(1,1,1);  //Blanc
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

        //Face du dessous 
        glColor3f(0,0,1); //Bleu        
        glVertex3f(x1, y1-2, z1);    
        glVertex3f(x2, y2-2, z2);
        glVertex3f(x3, y3-2, z3);
        glVertex3f(x4, y4-2, z4);

        glColor3f(1,1,1); //Blanc   

        glEnd();
    }
}

void afficher_decor()
{
    int x1 = -500;
    int y1 = -100;
    int z1 = -500;
    int x2 = 500;
    int y2 = -100;
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

    glEnd();

    int i;
    for(i=0; i<nb_element_decor; i++)
    {
        glBegin(GL_QUADS);
    
        int x1 = tab_decor[i].p1.x;
        int y1 = tab_decor[i].p1.y;
        int z1 = tab_decor[i].p1.z;
        int x2 = tab_decor[i].p2.x;
        int y2 = tab_decor[i].p2.y;
        int z2 = tab_decor[i].p2.z;
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        //Face dessus
            glColor3f(1,0,1); //Bleu
            /*glTexCoord2i(0,0);*/ glVertex3f(x1, y1, z1);    
            /*glTexCoord2i(0,1);*/ glVertex3f(x2, y1, z1);    
            glColor3f(0,1,0); //Bleu clair    
            /*glTexCoord2i(1,1);*/ glVertex3f(x2, y2, z2);
            /*glTexCoord2i(1,0);*/ glVertex3f(x1, y2, z2);

        glColor3f(1,1,1); //Blanc   

        glEnd();
    }

}

void definir_decor(int nombre)
{
    // point p1;
    // point p2;
    //FINIR CA    
    // ajouter_element_decor(p1,p2);
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

/*Ajoute une plate-forme grace a 4 points*/
void ajouter_plateforme(point p1, point p2, point p3, point p4)
{
    plateforme p;
    p.p1= p1;
    p.p2= p2;
    p.p3= p3;
    p.p4= p4;
    tab_plateformes[nb_plateformes++] = p;
}

void ajouter_element_decor(point p1, point p2, point p3, point p4)
{
    plateforme p;
    p.p1= p1;
    p.p2= p2;
    p.p3= p3;
    p.p4= p4;
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