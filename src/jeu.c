#include "jeu.h"

void initGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("La boule magique");
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glGenTextures(2,tex_sol);
    glBindTexture(GL_TEXTURE_2D, tex_sol[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    chargementTexture(&tex_sol[0], "test.png");
    //chargementTexture(&tex_sol[1], "test.png");
}

void majVecteurs()
{
    //Rayon de la boule
    brayon = 2;
    //Coordonnées du centre de la boule
    bx = 0;
    by = 50;
    bz = 0;
    //Vecteur de vitesse de la boule
    vx = 0;
    vy = 0;
    vz = 0;
    //Vecteur d'accélération de la boule
    ax = 0;
    ay = 0;
    az = 0;
    //Vecteur de gravité de la boule
    gx = 0;
    gy = -0.001;
    gz = 0;
    //Position de l'observateur
    if(!appartientPlateforme(bx, by + brayon*5, bz))
    {
        ox = bx;
        oy = by + brayon*5;
        oz = bz;
    }
}

void lancement()
{
    //Menu
    glutDisplayFunc(AffichageMenu);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavierMenu); //<= Lancera lancementJeu
    glutMainLoop();
}

void lancementJeu()
{
    majVecteurs();
    gestionMenu();

    nb_plateformes = 0;

    point p11 = nouveau_point(-30, 0, -30);
    point p12 = nouveau_point(-30, 0, 30);
    point p13 = nouveau_point(30, 0, 30);
    point p14 = nouveau_point(30, 0, -30);

    point p21 = nouveau_point(30, -10, 30);
    point p22 = nouveau_point(30, -20, 90);
    point p23 = nouveau_point(90, -20, 90);
    point p24 = nouveau_point(90, -10, 30);

    point p31 = nouveau_point(30, 30, 150);
    point p32 = nouveau_point(90, 30, 150);

    ajouter_plateforme(p11, p12, p13, p14);
    ajouter_plateforme(p21, p22, p23, p24);
    ajouter_plateforme(p31, p22, p23, p32);

    definir_decor(1);

    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavier);
    glutSpecialFunc(GestionSpecial);

    glutMainLoop();
}

//Fonction Affichage pour flutDisplayFunc

void Affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix() ;
    glLoadIdentity();
    //afficher_vecteurs();

    glFrustum(-1,1,-1,1,1,200);

    // char vx_string[50];
    // sprintf(vx_string, "%f", vx);
    // afficherText(10,0,0,1,1,vx_string);

    maj_position_boule();
    
    ax=0; ay=0; az=0;

    //maj caméra
    // float positionCameraX = bx-vx*400;//((bx-vx*400)>7)?bx-vx-7:((bx-vx*400)<-7)?bx-vx+7:bx-vx*400;
    // float positionCameraY = by+brayon*4;
    // float positionCameraZ = bz-vz*400;//((bz-vz*400)>7)?bz-vz-7:((bz-vz*400)<-7)?bz-vz+7:bz-vz*400;

    //Mise a jour de la caméra
    maj_observateur();
    gluLookAt(ox, oy, oz, bx, by+brayon, bz+1, 0, 1, 0);
    //printf("Vecteur caméra: %f %f %f\n", ox, oy, oz);


    //Affichage Boule
    dessiner_boule(brayon,bx,by,bz);

    afficher_plateformes();
    afficher_decor();

    trace_grille(5);
    glutSwapBuffers();
}


void Animer()
{
    glutPostRedisplay();
}


int appartientPlateforme(float x, float y, float z)
{
    return 0;
    // int i;
    // for (i=0; i<nb_plateformes; i++)
    // {
    //     int x1 = tab_plateformes[i].x1;
    //     int y1 = tab_plateformes[i].y1;
    //     int z1 = tab_plateformes[i].z1;
    //     int x2 = tab_plateformes[i].x2;
    //     int y2 = tab_plateformes[i].y2;
    //     int z2 = tab_plateformes[i].z2;
    
       
    // }
}