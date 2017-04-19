#include "decor.h"

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


void chargementTexture(GLuint* texture, char* chemin)
{
    *texture = SOIL_load_OGL_texture(chemin,
                                     SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID,
                                     SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT
                                    );
    if(*texture==NULL)
        fprintf(stderr,"Erreur de chargement de texture: \"%s\"\n", chemin);
}

void afficher_plateformes()
{
    int i;
    for (i=0; i<nb_plateformes; i++)
    {
        int x1 = tab_plateformes[i].x1;
        int y1 = tab_plateformes[i].y1;
        int z1 = tab_plateformes[i].z1;
        int x2 = tab_plateformes[i].x2;
        int y2 = tab_plateformes[i].y2;
        int z2 = tab_plateformes[i].z2;

        glBegin(GL_QUADS);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        //Face dessus
          glColor3f(1,1,1); //Blanc  
         glTexCoord2i(0,0); glVertex3f(x1, y1, z1);    
         glTexCoord2i(0,1); glVertex3f(x2, y1, z1);    
         glTexCoord2i(1,1); glVertex3f(x2, y2, z2);
         glTexCoord2i(1,0); glVertex3f(x1, y2, z2);

         //Bord 1
          glColor3f(0.9,0.9,0.9);  //Gris
         glVertex3f(x1, y1, z1);    
         glVertex3f(x2, y1, z1);
         glVertex3f(x2, y1-2, z1);
         glVertex3f(x1, y1-2, z1);

        //Bord 2
         glVertex3f(x1, y1, z1);    
         glVertex3f(x1, y2, z2);
         glVertex3f(x1, y2-2, z2);
         glVertex3f(x1, y1-2, z1);

        //Bord 3
         glVertex3f(x1, y2, z2);    
         glVertex3f(x2, y2, z2);
         glVertex3f(x2, y2-2, z2);
         glVertex3f(x1, y2-2, z2);

        //Bord 4
         glVertex3f(x2, y1, z1);    
         glVertex3f(x2, y2, z2);
         glVertex3f(x2, y2-2, z2);
         glVertex3f(x2, y1-2, z1);

        //Face du dessous 
         glVertex3f(x1, y1-2, z1);    
         glVertex3f(x2, y1-2, z1);
         glVertex3f(x2, y2-2, z2);
         glVertex3f(x1, y2-2, z2);
        
        glColor3f(1,1,1); //Blanc   

        glEnd();
    }
}

void ajouter_plateforme(int x1, int y1, int z1, int x2, int y2, int z2)
{
    plateforme p;
    p.x1 = x1;
    p.y1 = y1;
    p.z1 = z1;
    p.x2 = x2;
    p.y2 = y2;
    p.z2 = z2;
    tab_plateformes[nb_plateformes] = p;
    nb_plateformes++;
}

//Tracage de la grille des points
void trace_grille(int n)
{
    glColor3f(1.0,1.0,1.0); //Blanc
    
    //Afficher X et Y sur le repère
    afficherText(10,0,0,1,1,"X");
    afficherText(0,10,0,1,1,"Y");
    afficherText(-10,0,0,1,1,"X");
    afficherText(0,-10,0,1,1,"Y");
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