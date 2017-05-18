#include "jeu.h"

void initGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("La boule magique");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB); 

    glGenTextures(3, tex_sol);
    glGenTextures(6, tex_skybox);

    glBindTexture(GL_TEXTURE_2D, tex_sol[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    //INFO: Les chargements de textures sont faits dans LancementJeu()
}

void gestion_arguments(int argc, char** argv)
{
    int i;
    num_niveau = 0;
    if(argc>0)
    {
        for(i=0; i<argc; i++)
        {
            //Gestion de l'argument de debug pour ne pas afficher de texture
            if(strcmp(argv[i],"-notexture")==0 || strcmp(argv[i],"-notex")==0)
            {
                no_texture=1;
            }
            //Gestion du niveau spécifié en argument
            if(strcmp(argv[i],"-lvl")==0 && i+1<argc)
            {
                num_niveau=atoi(argv[++i])-1;
            }
        }
    }
    else // Cas normal: Texture et niveau 1
    {
        no_texture=0;
        num_niveau=1;
    }
}

void majVecteurs()
{
    //Rayon de la boule
    brayon = 2;
    // FAIT DANS definir_niveau()
    // //Coordonnées du centre de la boule
    // bx = 0;
    // by = 50;
    // bz = 0;
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
    ox = bx;
    oy = by + brayon*5;
    oz = bz;
    //Frottement
    fx = 0;
    fz = 0;
    //Direction avant de s'arrêter, on initialise pour partir direction x
    dx = 1;
    dz = 0;
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
    definir_decor(LARGEUR_ELEMENT_DECOR);

    init_texture();
    definir_niveau();

    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavier);
    glutSpecialFunc(GestionSpecial);

    glutMainLoop();
}

void init_texture()
{
    if(!no_texture)
    {
        chargementTexture(&tex_sol[0], "test.png");
        chargementTexture(&tex_sol[1], "test3.png");
        chargementTexture(&tex_skybox[0],"img/testLF.png");
        chargementTexture(&tex_skybox[1],"img/testRT.png");
        chargementTexture(&tex_skybox[2],"img/testDN.png");
        chargementTexture(&tex_skybox[3],"img/testUP.png");
        chargementTexture(&tex_skybox[4],"img/testFT.png");
        chargementTexture(&tex_skybox[5],"img/testBK.png");
    }
}

void definir_niveau()
{
    int i;
    //On ajoute chaque plateforme
    for(i=0; i<nombre_plateforme_niveau[num_niveau]; i++)
    {
        ajouter_plateforme_charge(plateforme_niveau[num_niveau][i]);
    }

    //On fixe le point de départ
    bx = point_depart_niveau[num_niveau].x;
    by = point_depart_niveau[num_niveau].y;
    bz = point_depart_niveau[num_niveau].z;

    
    printf("B = (%d,%d,%d)\n",point_depart_niveau[num_niveau].x,point_depart_niveau[num_niveau].y,point_depart_niveau[num_niveau].z);
    printf("num_niveau=%d\n",num_niveau);

    //On fixe le point d'arrivée
    goal = nouveau_point(   point_arrivee_niveau[num_niveau].x,
                            point_arrivee_niveau[num_niveau].y,
                            point_arrivee_niveau[num_niveau].z);

    
    // if(num_niveau==2)
    // {
    //     point p11 = nouveau_point(-15, 0, -15);
    //     point p12 = nouveau_point(-15, 0, 15);
    //     point p13 = nouveau_point(15, 0, 15);
    //     point p14 = nouveau_point(15, 0, -15);
    //     ajouter_plateforme(p11, p12, p13, p14);

    //     point p21 = nouveau_point(80, 0, -15);
    //     point p22 = nouveau_point(80, 0, 15);
    //     point p23 = nouveau_point(50, 0, 15);
    //     point p24 = nouveau_point(50, 0, -15);
    //     ajouter_plateforme(p21, p22, p23, p24);

    //     point p31 = nouveau_point(50, 0, 0);
    //     point p32 = nouveau_point(50, 0, 1);
    //     point p33 = nouveau_point(15, 0, 1);
    //     point p34 = nouveau_point(15, 0, 0);
    //     ajouter_plateforme(p31, p32, p33, p34);

    //     //Coordonnées du centre de la boule
    //     bx = 0;
    //     by = 15;
    //     bz = 0;
    // }
    // if(num_niveau==3)
    // {
    //     point p11 = nouveau_point(-30, 0, -30);
    //     point p12 = nouveau_point(-30, 0, 30);
    //     point p13 = nouveau_point(30, 0, 30);
    //     point p14 = nouveau_point(30, 0, -30);
    //     ajouter_plateforme(p11, p12, p13, p14);

    //     //Coordonnées du centre de la boule
    //     bx = 0;
    //     by = 50;
    //     bz = 0;
    // }
}

//Fonction Affichage pour flutDisplayFunc

void Affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix() ;
    glLoadIdentity();
    //afficher_vecteurs();

    glFrustum(-1,1,-1,1,1,1000);

    // char vx_string[50];
    // sprintf(vx_string, "%f", vx);
    // afficherText(10,0,0,1,1,vx_string);

    maj_position_boule();

    verification_limites();
    
    ax=0; ay=0; az=0;

    //maj caméra
    // float positionCameraX = bx-vx*400;//((bx-vx*400)>7)?bx-vx-7:((bx-vx*400)<-7)?bx-vx+7:bx-vx*400;
    // float positionCameraY = by+brayon*4;
    // float positionCameraZ = bz-vz*400;//((bz-vz*400)>7)?bz-vz-7:((bz-vz*400)<-7)?bz-vz+7:bz-vz*400;

    //Mise a jour de la caméra
    maj_observateur();
    gluLookAt(ox, oy, oz, bx, by+brayon, bz+0.0000001, 0, 1, 0);


    //Affichage Boule
    dessiner_boule(brayon,bx,by,bz);

    afficher_plateformes();
    afficher_decor();
    afficher_cubemap();

    trace_grille(5);
    glutSwapBuffers();
}

void verification_limites()
{
    if(bx>LIMITE_MAP || bx<-LIMITE_MAP || bz>LIMITE_MAP || bz<-LIMITE_MAP || by<-100)
    {
        bx=0; by=50; bz=0;
        ax=0; ay=0; az=0;
        vx=0; vy=0; vz=0;
    }
}

void Animer()
{
    glutPostRedisplay();
}

int appartientPlateforme(float x, float y, float z)
{
    return 0;
}
